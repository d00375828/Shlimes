import AsyncStorage from "@react-native-async-storage/async-storage";
import React, {
  createContext,
  useContext,
  useEffect,
  useMemo,
  useState,
} from "react";
import { TextStyle, ViewStyle } from "react-native";

type Theme = {
  name: string;
  bg: string;
  text: string;
  card: string;
  tint: string;
  buttonBg: string;
  inputBg: string;
};

export const THEMES: Record<string, Theme> = {
  lBlue: {
    name: "Light Blue",
    bg: "#F7FAFF",
    text: "#0B1220",
    card: "#FFFFFF",
    tint: "#0A84FF",
    buttonBg: "#E6F0FF",
    inputBg: "#F0F4FF",
  },
  lGreen: {
    name: "Light Green",
    bg: "#FAFFF7",
    text: "#0F1A0F",
    card: "#FFFFFF",
    tint: "#34C759",
    buttonBg: "#E8F9EE",
    inputBg: "#F1FBF5",
  },
  lPink: {
    name: "Light Pink",
    bg: "#FFF7FA",
    text: "#0B1220",
    card: "#FFFFFF",
    tint: "#FF4D8D",
    buttonBg: "#FFE5EE",
    inputBg: "#FFEEF4",
  },
  dBlue: {
    name: "Dark Blue",
    bg: "#0B1220",
    text: "#EAF2FF",
    card: "#121A2A",
    tint: "#5AC8FA",
    buttonBg: "#0F1A30",
    inputBg: "#172036",
  },
  dPurple: {
    name: "Dark Purple",
    bg: "#151022",
    text: "#F0E6FF",
    card: "#1B1630",
    tint: "#BF5AF2",
    buttonBg: "#221B3D",
    inputBg: "#241F3E",
  },
  dGray: {
    name: "Dark Gray",
    bg: "#121212",
    text: "#EDEDED",
    card: "#1C1C1E",
    tint: "#98989D",
    buttonBg: "#2A2A2C",
    inputBg: "#1E1E20",
  },
};

type ThemeCtx = {
  theme: Theme;
  setThemeName: (name: keyof typeof THEMES) => void;
};
const ThemeContext = createContext<ThemeCtx | null>(null);
const THEME_KEY = "theme_name_v1";
const DEFAULT_NAME: keyof typeof THEMES = "lBlue";

export function ThemeProvider({ children }: { children: React.ReactNode }) {
  const [name, setName] = useState<keyof typeof THEMES>(DEFAULT_NAME);
  const [ready, setReady] = useState(false);

  useEffect(() => {
    (async () => {
      const stored = await AsyncStorage.getItem(THEME_KEY);
      if (stored && THEMES[stored]) setName(stored as keyof typeof THEMES);
      setReady(true);
    })();
  }, []);

  const setThemeName = async (n: keyof typeof THEMES) => {
    setName(n);
    await AsyncStorage.setItem(THEME_KEY, n);
  };

  const value = useMemo(() => ({ theme: THEMES[name], setThemeName }), [name]);

  if (!ready) return null;
  return (
    <ThemeContext.Provider value={value}>{children}</ThemeContext.Provider>
  );
}

export function useTheme() {
  const ctx = useContext(ThemeContext);
  if (!ctx) throw new Error("useTheme must be used inside ThemeProvider");
  return ctx;
}

export const stylesFromTheme = (t: Theme) => ({
  screen: { flex: 1, backgroundColor: t.bg } as ViewStyle,
  card: { backgroundColor: t.card, borderRadius: 12, padding: 12 } as ViewStyle,
  text: { color: t.text } as TextStyle,
  input: {
    backgroundColor: t.inputBg,
    color: t.text,
    padding: 10,
    borderRadius: 8,
  } as TextStyle,
  button: {
    backgroundColor: t.buttonBg,
    padding: 10,
    borderRadius: 10,
    alignItems: "center",
  } as ViewStyle,
  buttonText: { color: t.text, fontWeight: "600" } as TextStyle,
});
