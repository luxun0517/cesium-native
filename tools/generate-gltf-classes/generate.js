const createExtensionsProperty = require("./createExtensionsProperty");
const fs = require("fs");
const getNameFromSchema = require("./getNameFromSchema");
const indent = require("./indent");
const lodash = require("lodash");
const path = require("path");
const resolveProperty = require("./resolveProperty");
const unindent = require("./unindent");

function generate(options, schema) {
  const { schemaCache, config, outputDir, readerOutputDir } = options;

  const name = getNameFromSchema(config, schema);
  const thisConfig = config.classes[schema.title] || {};

  console.log(`Generating ${name}`);

  let base = "ExtensibleObject";
  if (schema.allOf && schema.allOf.length > 0 && schema.allOf[0].$ref) {
    const baseSchema = schemaCache.load(schema.allOf[0].$ref);
    base = getNameFromSchema(config, baseSchema);
  }

  const required = schema.required || [];

  const properties = Object.keys(schema.properties)
    .map((key) =>
      resolveProperty(schemaCache, config, name, key, schema.properties[key], required)
    )
    .filter((property) => property !== undefined);

  const extensionsProperty = createExtensionsProperty(options.extensions[schema.title], name, schema);
  if (extensionsProperty) {
    properties.push(extensionsProperty);
  }

  const localTypes = lodash.uniq(
    lodash.flatten(properties.map((property) => property.localTypes))
  );

  const headers = lodash.uniq([
      `"CesiumGltf/Library.h"`,
      `"CesiumGltf/${base}.h"`,
      ...lodash.flatten(properties.map((property) => property.headers))
  ]);

  headers.sort();

  const header = `
        // This file was generated by generate-gltf-classes.
        // DO NOT EDIT THIS FILE!
        #pragma once

        ${headers.map((header) => `#include ${header}`).join("\n")}
        
        namespace CesiumGltf {
            /**
             * @brief ${schema.description}
             */
            struct CESIUMGLTF_API ${name}${thisConfig.toBeInherited ? "Spec" : (thisConfig.isBaseClass ? "" : " final")} : public ${base} {
                ${indent(localTypes.join("\n\n"), 16)}

                ${indent(
                  properties
                    .map((property) => formatProperty(property))
                    .filter(propertyText => propertyText !== undefined)
                    .join("\n\n"),
                  16
                )}
                ${thisConfig.toBeInherited ? privateSpecConstructor(name) : ""}
            };
        }
    `;

  const headerOutputDir = path.join(outputDir, "include", "CesiumGltf");
  fs.mkdirSync(headerOutputDir, { recursive: true });
  const headerOutputPath = path.join(headerOutputDir, `${name}${thisConfig.toBeInherited ? "Spec" : ""}.h`);
  fs.writeFileSync(headerOutputPath, unindent(header), "utf-8");

  const readerHeaders = lodash.uniq(
    [
      "<CesiumGltf/Reader.h>",
      `"${base}JsonHandler.h"`, 
      ...lodash.flatten(properties.map((property) => property.readerHeaders))
    ]
  );
  readerHeaders.sort();

  const readerLocalTypes = lodash.uniq(
    lodash.flatten(properties.map((property) => property.readerLocalTypes))
  );

  const readerHeader = `
        // This file was generated by generate-gltf-classes.
        // DO NOT EDIT THIS FILE!
        #pragma once

        ${readerHeaders.map((header) => `#include ${header}`).join("\n")}

        namespace CesiumGltf {
          struct ${name};

          class ${name}JsonHandler : public ${base}JsonHandler {
          public: 
            ${name}JsonHandler(ReadModelOptions options) noexcept;
            void reset(IJsonHandler* pHandler, ${name}* pObject);
            ${name}* getObject();
            virtual void reportWarning(const std::string& warning, std::vector<std::string>&& context = std::vector<std::string>()) override;

            virtual IJsonHandler* Key(const char* str, size_t length, bool copy) override;

          protected:
            IJsonHandler* ${name}Key(const char* str, ${name}& o);
    
          private:
            ${indent(readerLocalTypes.join("\n\n"), 12)}

            ${name}* _pObject = nullptr;
            ${indent(
              properties
                .map((property) => formatReaderProperty(property))
                .join("\n"),
              12
            )}
          };
        }
  `;

  const readerHeaderOutputDir = path.join(readerOutputDir, "generated");
  fs.mkdirSync(readerHeaderOutputDir, { recursive: true });
  const readerHeaderOutputPath = path.join(readerHeaderOutputDir, name + "JsonHandler.h");
  fs.writeFileSync(readerHeaderOutputPath, unindent(readerHeader), "utf-8");

  const readerLocalTypesImpl = lodash.uniq(
    lodash.flatten(properties.map((property) => property.readerLocalTypesImpl))
  );

  const readerHeadersImpl = lodash.uniq(
    [...lodash.flatten(properties.map((property) => property.readerHeadersImpl))]
  );
  readerHeadersImpl.sort();

function generateReaderOptionsInitializerList(properties, varName) {
    const initializerList = properties
      .filter(p => p.readerType.toLowerCase().indexOf("jsonhandler") != -1)
      .map(p => `_${p.name}(${varName})`)
      .join(", ");
    return initializerList == "" ? "" : ", " + initializerList;
}
  const readerImpl = `
        // This file was generated by generate-gltf-classes.
        // DO NOT EDIT THIS FILE!
        #include "${name}JsonHandler.h"
        #include "CesiumGltf/${name}.h"
        ${readerHeadersImpl.map((header) => `#include ${header}`).join("\n")}
        #include <cassert>
        #include <string>

        using namespace CesiumGltf;

        ${name}JsonHandler::${name}JsonHandler(ReadModelOptions options) noexcept : ${base}JsonHandler(options)${generateReaderOptionsInitializerList(properties, 'options')} {}

        void ${name}JsonHandler::reset(IJsonHandler* pParent, ${name}* pObject) {
          ${base}JsonHandler::reset(pParent, pObject);
          this->_pObject = pObject;
        }

        ${name}* ${name}JsonHandler::getObject() {
          return this->_pObject;
        }

        void ${name}JsonHandler::reportWarning(const std::string& warning, std::vector<std::string>&& context) {
          if (this->getCurrentKey()) {
            context.emplace_back(std::string(".") + this->getCurrentKey());
          }
          this->parent()->reportWarning(warning, std::move(context));
        }

        IJsonHandler* ${name}JsonHandler::Key(const char* str, size_t /*length*/, bool /*copy*/) {
          assert(this->_pObject);
          return this->${name}Key(str, *this->_pObject);
        }

        IJsonHandler* ${name}JsonHandler::${name}Key(const char* str, ${name}& o) {
          using namespace std::string_literals;

          ${indent(
            properties
              .map((property) => formatReaderPropertyImpl(property))
              .join("\n"),
            10
          )}

          return this->${base}Key(str, *this->_pObject);
        }

        ${indent(readerLocalTypesImpl.join("\n\n"), 8)}
  `;

  const readerSourceOutputPath = path.join(readerHeaderOutputDir, name + "JsonHandler.cpp");
  fs.writeFileSync(readerSourceOutputPath, unindent(readerImpl), "utf-8");

  return lodash.uniq(
    lodash.flatten(properties.map((property) => property.schemas))
  );
}

function formatProperty(property) {
  if (!property.type) {
    return undefined;
  }

  let result = "";

  result += `/**\n * @brief ${property.briefDoc || property.name}\n`;
  if (property.fullDoc) {
    result += ` *\n * ${property.fullDoc.split("\n").join("\n * ")}\n`;
  }

  result += ` */\n`;

  result += `${property.type} ${property.name}`;

  if (property.defaultValue !== undefined) {
    result += " = " + property.defaultValue;
  } else if (property.needsInitialization) {
    result += " = " + property.type + "()";
  }

  result += ";";

  return result;
}

function formatReaderProperty(property) {
  return `${property.readerType} _${property.name};`
}

function formatReaderPropertyImpl(property) {
  return `if ("${property.name}"s == str) return property("${property.name}", this->_${property.name}, o.${property.name});`;
}

function privateSpecConstructor(name) {
  return `
    private:
      /**
       * @brief This class is not mean to be instantiated directly. Use {@link ${name}} instead.
       */
      ${name}Spec() = default;
      friend struct ${name};
  `;
}

module.exports = generate;
