type HelloInput = {
  world: string;
};
type HelloOutput = {
  world: string;
};

export type JSEvents = {
  hello: (input: HelloInput) => HelloOutput;
};

type HelloInput = {
  world: string;
};
type HelloOutput = {
  world: number;
};

export type CppEvents = {
  hello: (input: HelloInput) => HelloOutput;
};
