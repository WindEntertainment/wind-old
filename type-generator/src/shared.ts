export type SchemaObject = { [paramName: string]: SchemaObject | string | SchemaTypes };
export type SchemaPlainObject = { [paramName: string]: string | SchemaTypes };

export type MethodSchema = {
  [className: string]: {
    methods: {
      [methodName: string]: {
        input: SchemaObject;
        output: SchemaObject;
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
  BOOLEAN = "boolean",
  NUMBER = "number",
  STRING = "string",
}

export const mappers: Record<Language, Record<SchemaTypes, string>> = {
  cpp: {
    [SchemaTypes.BOOLEAN]: "bool" ,
    [SchemaTypes.NUMBER]: "int" ,
    [SchemaTypes.STRING]: "std::string" ,
  },
  ts: {
    [SchemaTypes.BOOLEAN]: "boolean" ,
    [SchemaTypes.NUMBER]: "number" ,
    [SchemaTypes.STRING]: "string" ,
  },
};
