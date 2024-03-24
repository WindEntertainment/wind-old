"use client";

import { tw } from "@/tw";
import { Title } from "@radix-ui/react-toast";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const ToastTitle = forwardRef<ElementRef<typeof Title>, ComponentPropsWithoutRef<typeof Title>>(
  ({ className, ...props }, ref) => (
    <Title className={tw("text-sm [&+div]:text-xs font-semibold", className)} ref={ref} {...props} />
  ),
);
ToastTitle.displayName = Title.displayName;
