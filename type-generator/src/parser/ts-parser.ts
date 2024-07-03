import { MethodSchema, SchemaObject, SchemaPlainObject, SchemaTypes, capitalizeFirstLetter, mappers } from "../shared";

const mapTypeToTS = (type: SchemaTypes | string) => {
  // @ts-expect-error
  return mappers.ts?.[type] ?? type;
};

const generateType = (name: string, fields: SchemaPlainObject) => {
  if (typeof fields === "string") {
    return `type ${name} = ${fields};\n`;
  } else {
    let type = "";

    for (const [field, datatype] of Object.entries(fields)) {
      type += `  ${field}: ${mapTypeToTS(datatype)};\n`;
    }

    return `type ${name} = {\n` + type + "};\n";
  }
};

const generateNestedTypes = (name: string, fields: SchemaObject) => {
  let innerTypes = "";

  let type: SchemaPlainObject = {};

  if (typeof fields === "string") {
    type = fields;
  } else {
    for (const [field, datatype] of Object.entries(fields)) {
      if (typeof datatype === "string") {
        type[field] = datatype;
      } else {
        type[field] = name + capitalizeFirstLetter(field);
        innerTypes += generateNestedTypes(name + capitalizeFirstLetter(field), datatype);
      }
    }
  }
  return innerTypes + generateType(name, type);
};

function generateStruct(className: string, classSchema: MethodSchema[string]) {
  let classCode = "";

  let methodsCode = `\n export type Methods = {\n`;

  const { methods } = classSchema;

  for (const methodName in methods) {
    const { input, output } = methods[methodName];
    const upperMethodName = capitalizeFirstLetter(methodName);

    classCode += `namespace ${upperMethodName} {\n`;
    classCode += generateNestedTypes(`Input`, input);
    classCode += generateNestedTypes(`Output`, output);
    classCode += `}`;

    methodsCode += `  ${methodName}: (input: ${upperMethodName}.Input) => ${upperMethodName}.Output;\n`;
  }
  methodsCode += `};\n`;

  return `export namespace ${className}{${classCode}${methodsCode}};\n\n`;
}

export const parseTS = (schema: MethodSchema) => {
  let types = "";

  for (const className in schema) {
    types += generateStruct(className, schema[className]);
  }

  return types;
};
