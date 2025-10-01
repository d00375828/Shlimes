import { MaterialCommunityIcons } from "@expo/vector-icons";
import React from "react";
import { Pressable, Text, View } from "react-native";
import { Crime } from "../lib/storage";
import { stylesFromTheme, useTheme } from "./Theme";

export function CrimeItem({ crime, onPress }: { crime: Crime; onPress: () => void }) {
  const { theme } = useTheme();
  const S = stylesFromTheme(theme);
  return (
    <Pressable
      onPress={onPress}
      style={({ pressed }) => [
        { padding: 14, borderBottomWidth: 1, borderBottomColor: theme.buttonBg, flexDirection: "row", alignItems: "center" },
        pressed && { opacity: 0.6 },
      ]}
    >
      <View style={{ flex: 1 }}>
        <Text style={[S.text, { fontWeight: "600", marginBottom: 4 }]} numberOfLines={1}>
          {crime.title || "(Untitled Crime)"}
        </Text>
        <Text style={[S.text, { opacity: 0.7 }]}>{new Date(crime.dateISO).toDateString()}</Text>
      </View>
      {crime.solved && <MaterialCommunityIcons name="handcuffs" size={22} color={theme.tint} />}
    </Pressable>
  );
}
