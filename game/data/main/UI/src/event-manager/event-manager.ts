import { CppEvents, JSEvents } from "../generated/ui";

export const cppEvents: CppEvents = {
  hello: ({ world }) => {
    console.log("Hello world!", world);

    return { world: "123" };
  },
};

export const jsEvents: JSEvents = {
  hello: ({ world }) => {
    console.log("Hello world!", world);

    return { world: "123" };
  },
};

export const triggerJS = <T extends keyof JSEvents>({ data, name }: { data: Parameters<JSEvents[T]>[0]; name: T }) => {
  jsEvents[name](data);
};

export const triggerCpp = <T extends keyof CppEvents>({
  data,
  name,
}: {
  data: Parameters<CppEvents[T]>[0];
  name: T;
}) => {
  cppEvents[name](data);
};
