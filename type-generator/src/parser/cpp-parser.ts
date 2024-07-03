import { MethodSchema, SchemaObject, SchemaPlainObject, SchemaTypes, capitalizeFirstLetter, mappers } from "../shared";

const mapTypeToCpp = (type: SchemaTypes | string) => {
  // @ts-expect-error
  return mappers.cpp?.[type] ?? type;
};

const generateStruct = (name: string, fields: SchemaPlainObject) => {
  let struct = "";

  if (typeof fields === "string") {
    return `struct ${name} = ${fields};\n`;
  } else {
    for (const [field, datatype] of Object.entries(fields)) {
      struct += `    ${mapTypeToCpp(datatype)} ${field};\n`;
    }
    return `  struct ${name} {\n` + struct + "  };\n";
  }
};

const generateNestedStructs = (name: string, fields: SchemaObject) => {
  let innerStructs = "";

  let struct: SchemaPlainObject = {};

  if (typeof fields === "string") {
    struct = fields;
  } else {
    for (const [field, datatype] of Object.entries(fields)) {
      if (typeof datatype === "string") {
        struct[field] = datatype;
      } else {
        struct[field] = name + capitalizeFirstLetter(field);
        innerStructs += generateNestedStructs(name + capitalizeFirstLetter(field), datatype);
      }
    }
  }

  return innerStructs + generateStruct(name, struct);
};

function generateClass(className: string, classSchema: MethodSchema[string]) {
  let classCode = "";
  let methodsCode = `\n class Methods {\n`;

  const { methods } = classSchema;

  for (const methodName in methods) {
    const { input, output } = methods[methodName];
    const upperMethodName = capitalizeFirstLetter(methodName);

    classCode += `namespace ${upperMethodName} {\n`;
    classCode += generateNestedStructs(`Input`, input);
    classCode += generateNestedStructs(`Output`, output);
    classCode += `}`;

    methodsCode += `  ${upperMethodName}::Output ${methodName}(const ${upperMethodName}::Input& input);\n\n`;
  }

  return `\nnamespace ${className}{${classCode}${methodsCode}};};\n\n`;
}

export const parseCpp = (schema: MethodSchema) => {
  let structs = "";

  for (const className in schema) {
    structs += generateClass(className, schema[className]);
  }

  return structs;
};
