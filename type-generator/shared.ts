export type SchemaObject = { [paramName: string]: SchemaObject | string };
export type SchemaPlainObject = { [paramName: string]: string };

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

export const mappers: Record<Language, Record<string, SchemaTypes>> = {
  cpp: {
    bool: SchemaTypes.BOOLEAN,
    int: SchemaTypes.NUMBER,
    "std::string": SchemaTypes.STRING,
  },
  ts: {
    boolean: SchemaTypes.BOOLEAN,
    number: SchemaTypes.NUMBER,
    string: SchemaTypes.STRING,
  },
};
