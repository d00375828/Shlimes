import { Stack } from "expo-router";
import React from "react";
import { ThemeProvider, useTheme } from "../components/Theme";

function LayoutInner() {
  const { theme } = useTheme();
  return (
    <Stack
      screenOptions={{
        headerStyle: { backgroundColor: theme.card },
        headerTitleStyle: { color: theme.text },
        headerTintColor: theme.tint,
      }}
    />
  );
}

export default function RootLayout() {
  return (
    <ThemeProvider>
      <LayoutInner />
    </ThemeProvider>
  );
}
