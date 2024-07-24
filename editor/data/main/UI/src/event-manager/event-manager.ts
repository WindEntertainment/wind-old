import { CppEvents, JsEvents } from "../generated/ui";

const jsEvents: JsEvents.Methods = {
  loadProject: ({ maps, name }) => {
    console.log(JSON.stringify({ maps, name }));
    return { success: true };
  },
};

window.emitJSEvent = args => {
  const event = JSON.parse(args);
  // @ts-expect-error 123
  jsEvents?.[event?.name]?.(event?.data);
};

export const triggerCppEvent = <T extends keyof CppEvents.Methods>(event: {
  data: Parameters<CppEvents.Methods[T]>[0];
  name: T;
}) => {
  emitCppEvent(JSON.stringify(event));
};
