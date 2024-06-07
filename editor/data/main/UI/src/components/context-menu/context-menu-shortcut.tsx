"use client";
import { tw } from "@/tw";
import { FC, HTMLAttributes } from "react";

export const ContextMenuShortcut: FC<HTMLAttributes<HTMLSpanElement>> = ({ className, ...props }) => {
  return (
    <span className={tw("text-xs ml-auto tracking-widest text-stone-500 dark:text-stone-400", className)} {...props} />
  );
};
ContextMenuShortcut.displayName = "ContextMenuShortcut";
