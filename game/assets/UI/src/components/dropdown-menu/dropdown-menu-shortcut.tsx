"use client";
import { tw } from "@/tailwind";
import { FC, HTMLAttributes } from "react";

export const DropdownMenuShortcut: FC<HTMLAttributes<HTMLSpanElement>> = ({ className, ...props }) => {
  return <span className={tw("text-xs ml-auto tracking-widest opacity-60", className)} {...props} />;
};
DropdownMenuShortcut.displayName = "DropdownMenuShortcut";
