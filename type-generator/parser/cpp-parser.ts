import { MethodSchema, SchemaObject, SchemaPlainObject, capitalizeFirstLetter, mappers } from "../shared";

const mapTypeToCpp = (type: string) => {
  return mappers.cpp[type] ?? type;
};

const generateStruct = (name: string, fields: SchemaPlainObject) => {
  let struct = "";

  for (const [field, datatype] of Object.entries(fields)) {
    struct += `    ${mapTypeToCpp(datatype)} ${field};\n`;
  }

  return `  struct ${name} {\n` + struct + "  };\n";
};

const generateNestedStructs = (name: string, fields: SchemaObject) => {
  let innerStructs = "";

  const struct: Record<string, string> = {};

  for (const [field, datatype] of Object.entries(fields)) {
    if (typeof datatype === "string") {
      struct[field] = datatype;
    } else {
      struct[field] = name + capitalizeFirstLetter(field);
      innerStructs += generateNestedStructs(name + capitalizeFirstLetter(field), datatype);
    }
  }

  return innerStructs + generateStruct(name, struct);
};

function generateClass(className: string, classSchema: MethodSchema[string]) {
  let classCode = "";

  const { methods } = classSchema;

  for (const methodName in methods) {
    const { input, output } = methods[methodName];
    const upperMethodName = capitalizeFirstLetter(methodName);

    classCode += generateNestedStructs(`${upperMethodName}Input`, input);
    classCode += generateNestedStructs(`${upperMethodName}Output`, output);

    classCode += `  ${upperMethodName}Output ${methodName}(const ${upperMethodName}Input& input) const;\n\n`;
  }

  return `\nclass ${className} {\n` + classCode + "};\n";
}

export const parseCpp = (schema: MethodSchema) => {
  let structs = "";

  for (const className in schema) {
    structs += generateClass(className, schema[className]);
  }

  return structs;
};
