import { Ionicons } from "@expo/vector-icons";
import { useFocusEffect } from "@react-navigation/native";
import { Stack, useNavigation, useRouter } from "expo-router";
import React, { useCallback, useLayoutEffect, useState } from "react";
import { FlatList, Pressable, View } from "react-native";
import { SafeAreaView } from "react-native-safe-area-context";
import { CrimeItem } from "../components/CrimeStuffs";
import { stylesFromTheme, useTheme } from "../components/Theme";
import { Crime, loadCrimes, uuid } from "../lib/storage";

export default function IndexScreen() {
  const router = useRouter();
  const nav = useNavigation();
  const { theme } = useTheme();
  const S = stylesFromTheme(theme);

  const [crimes, setCrimes] = useState<Crime[]>([]);

  const refresh = useCallback(() => {
    loadCrimes().then(setCrimes);
  }, []);

  useFocusEffect(
    useCallback(() => {
      refresh();
    }, [refresh])
  );

  useLayoutEffect(() => {
    nav.setOptions({
      title: "Criminal Intent",
      headerRight: () => (
        <View style={{ flexDirection: "row", gap: 16, marginRight: 8 }}>
          <Pressable
            onPress={() => {
              const id = uuid();
              router.push({ pathname: "/crime/[id]", params: { id } });
            }}
          >
            <Ionicons name="add" size={26} color={theme.tint} />
          </Pressable>

          <Pressable onPress={() => router.push("/settings")}>
            <Ionicons name="settings-outline" size={24} color={theme.tint} />
          </Pressable>
        </View>
      ),
    });
  }, [nav, router, theme.tint]);

  const renderItem = ({ item }: { item: Crime }) => (
    <CrimeItem
      crime={item}
      onPress={() =>
        router.push({ pathname: "/crime/[id]", params: { id: item.id } })
      }
    />
  );

  return (
    <SafeAreaView style={S.screen}>
      <Stack.Screen options={{ headerShown: true }} />
      <FlatList
        data={crimes}
        keyExtractor={(c) => c.id}
        renderItem={renderItem}
        contentContainerStyle={{ backgroundColor: theme.card }}
      />
    </SafeAreaView>
  );
}
