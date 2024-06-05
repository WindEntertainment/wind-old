import { MethodSchema, SchemaObject, SchemaPlainObject, SchemaTypes, capitalizeFirstLetter, mappers } from "../shared";

const mapTypeToTS = (type: SchemaTypes | string) => {
  // @ts-expect-error
  return mappers.ts?.[type] ?? type;
};

const generateType = (name: string, fields: SchemaPlainObject) => {
  let type = "";

  for (const [field, datatype] of Object.entries(fields)) {
    type += `  ${field}: ${mapTypeToTS(datatype)};\n`;
  }

  return `type ${name} = {\n` + type + "};\n";
};

const generateNestedTypes = (name: string, fields: SchemaObject) => {
  let innerTypes = "";

  const type: Record<string, string> = {};

  for (const [field, datatype] of Object.entries(fields)) {
    if (typeof datatype === "string") {
      type[field] = datatype;
    } else {
      type[field] = name + capitalizeFirstLetter(field);
      innerTypes += generateNestedTypes(name + capitalizeFirstLetter(field), datatype);
    }
  }

  return innerTypes + generateType(name, type);
};

function generateStruct(className: string, classSchema: MethodSchema[string]) {
  let classCode = "";

  let methodsCode = `\nexport type ${className} = {\n`;

  const { methods } = classSchema;

  for (const methodName in methods) {
    const { input, output } = methods[methodName];
    const upperMethodName = capitalizeFirstLetter(methodName);

    classCode += generateNestedTypes(`${upperMethodName}Input`, input);
    classCode += generateNestedTypes(`${upperMethodName}Output`, output);

    methodsCode += `  ${methodName}: (input: ${upperMethodName}Input) => ${upperMethodName}Output;\n`;
  }
  methodsCode += `};\n\n`;

  return classCode + methodsCode;
}

export const parseTS = (schema: MethodSchema) => {
  let types = "";

  for (const className in schema) {
    types += generateStruct(className, schema[className]);
  }

  return types;
};
