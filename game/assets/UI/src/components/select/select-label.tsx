"use client";
import { tw } from "@/tailwind";
import { Label } from "@radix-ui/react-select";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const SelectLabel = forwardRef<ElementRef<typeof Label>, ComponentPropsWithoutRef<typeof Label>>(
  ({ className, ...props }, ref) => (
    <Label className={tw("text-sm px-2 py-1.5 font-semibold", className)} ref={ref} {...props} />
  ),
);
SelectLabel.displayName = Label.displayName;
