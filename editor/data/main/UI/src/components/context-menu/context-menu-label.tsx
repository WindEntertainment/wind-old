"use client";
import { tw } from "@/tw";
import { Label } from "@radix-ui/react-context-menu";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const ContextMenuLabel = forwardRef<
  ElementRef<typeof Label>,
  {
    inset?: boolean;
  } & ComponentPropsWithoutRef<typeof Label>
>(({ className, inset, ...props }, ref) => (
  <Label
    className={tw("text-sm px-2 py-1.5 font-semibold text-stone-950 dark:text-stone-50", inset && "pl-8", className)}
    ref={ref}
    {...props}
  />
));
ContextMenuLabel.displayName = Label.displayName;
