"use client";
import { tw } from "@/tw";
import { Label } from "@radix-ui/react-dropdown-menu";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const DropdownMenuLabel = forwardRef<
  ElementRef<typeof Label>,
  {
    inset?: boolean;
  } & ComponentPropsWithoutRef<typeof Label>
>(({ className, inset, ...props }, ref) => (
  <Label className={tw("text-sm px-2 py-1.5 font-semibold", inset && "pl-8", className)} ref={ref} {...props} />
));
DropdownMenuLabel.displayName = Label.displayName;
