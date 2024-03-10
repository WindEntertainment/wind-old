"use client";

import { tw } from "@/tailwind";
import { FC, HTMLAttributes } from "react";

export const CommandShortcut: FC<HTMLAttributes<HTMLSpanElement>> = ({ className, ...props }) => {
  return (
    <span className={tw("text-xs ml-auto tracking-widest text-stone-500 dark:text-stone-400", className)} {...props} />
  );
};
CommandShortcut.displayName = "CommandShortcut";
