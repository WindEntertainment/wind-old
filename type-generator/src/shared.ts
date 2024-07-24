export type SchemaObject = { [paramName: string]: SchemaObject | string | SchemaTypes } | string;
export type SchemaPlainObject = { [paramName: string]: string | SchemaTypes } | string;

export type MethodSchema = {
  header?: string;
  classes: {
    [className: string]: {
      methods: {
        [methodName: string]: {
          input: SchemaObject;
          output: SchemaObject;
        };
      };
    };
  };
};

export const capitalizeFirstLetter = (str: string) => {
  return str.charAt(0).toUpperCase() + str.slice(1);
};

export enum Language {
  CPP = "cpp",
  TS = "ts",
}

export enum SchemaTypes {
  BOOLEAN = "bool",
  INT = "int",
  FLOAT = "float",
  STD_STRING = "std::string",
  VOID = "void",
}

export const mappers: Record<Language, Record<SchemaTypes, string>> = {
  cpp: {
    [SchemaTypes.BOOLEAN]: "bool",
    [SchemaTypes.INT]: "int",
    [SchemaTypes.FLOAT]: "float",
    [SchemaTypes.STD_STRING]: "std::string",
    [SchemaTypes.VOID]: "void",
  },
  ts: {
    [SchemaTypes.BOOLEAN]: "boolean",
    [SchemaTypes.INT]: "number",
    [SchemaTypes.FLOAT]: "number",
    [SchemaTypes.STD_STRING]: "string",
    [SchemaTypes.VOID]: "void",
  },
};

export type ParserConfigs = {
  language: Language;
  outputPath: string;
  schemaPath: string;
};
