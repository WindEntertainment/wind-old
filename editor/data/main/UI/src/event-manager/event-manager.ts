// import { CppEvents, JSEvents } from "../../type-generator/Events";

// export const cppEvents: CppEvents = {
//   loadImage: ({ projectName }) => {
//     console.log(projectName);
//   },
//   loadProject: () => {
//     return { projectName: "" };
//   },
// };

// export const jsEvents: JSEvents = {
//   toggleLeftBar: () => {
//     return { projectName: "" };
//   },
//   toggleMinimap: ({ show }) => {
//     console.log(show);
//   },
// };

// export const triggerJS = <T extends keyof JSEvents>({ data, name }: { data: Parameters<JSEvents[T]>[0]; name: T }) => {
//   // @ts-expect-error wrong data typing
//   jsEvents[name](data);
// };

// export const triggerCpp = <T extends keyof CppEvents>({
//   data,
//   name,
// }: {
//   data: Parameters<CppEvents[T]>[0];
//   name: T;
// }) => {
//   // @ts-expect-error wrong data typing
//   cppEvents[name](data);
// };
export {};
