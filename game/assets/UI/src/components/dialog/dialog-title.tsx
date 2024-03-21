"use client";
import { Title } from "@radix-ui/react-dialog";
import { tw } from "@/tw";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const DialogTitle = forwardRef<ElementRef<typeof Title>, ComponentPropsWithoutRef<typeof Title>>(
  ({ className, ...props }, ref) => (
    <Title className={tw("text-lg font-semibold leading-none tracking-tight", className)} ref={ref} {...props} />
  ),
);
DialogTitle.displayName = Title.displayName;
