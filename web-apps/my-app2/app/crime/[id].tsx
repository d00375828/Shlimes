// Crime details page

import { Ionicons } from "@expo/vector-icons";
import DateTimePicker from "@react-native-community/datetimepicker";
import ExpoCheckbox from "expo-checkbox";
import * as ImagePicker from "expo-image-picker";
import { useLocalSearchParams, useNavigation, useRouter } from "expo-router";
import React, { useEffect, useLayoutEffect, useState } from "react";
import {
  Alert,
  Image,
  Modal,
  Platform,
  Pressable,
  Text,
  TextInput,
  View,
} from "react-native";
import { SafeAreaView } from "react-native-safe-area-context";
import { stylesFromTheme, useTheme } from "../../components/Theme";
import { Crime, getCrime, upsertCrime } from "../../lib/storage";

export default function CrimeDetail() {
  const { id } = useLocalSearchParams<{ id: string }>();
  const nav = useNavigation();
  const router = useRouter();
  const { theme } = useTheme();
  const S = stylesFromTheme(theme);

  const [title, setTitle] = useState("");
  const [details, setDetails] = useState("");
  const [date, setDate] = useState<Date>(new Date());
  const [solved, setSolved] = useState(false);
  const [photoUri, setPhotoUri] = useState<string | undefined>(undefined);

  const [dateOpen, setDateOpen] = useState(false);

  useLayoutEffect(() => {
    nav.setOptions({
      title: "Crime Detail",
      headerBackVisible: false,
      headerLeft: () => (
        <Pressable
          onPress={() => nav.goBack()}
          hitSlop={8}
          style={{ paddingHorizontal: 8 }}
        >
          <Ionicons name="chevron-back" size={24} color={theme.tint} />
        </Pressable>
      ),
      headerRight: () => (
        <Pressable
          onPress={() => router.push("/settings")}
          style={{ marginRight: 8 }}
        >
          <Ionicons name="settings-outline" size={24} color={theme.tint} />
        </Pressable>
      ),
    });
  }, [nav, router, theme.tint]);

  useEffect(() => {
    getCrime(id).then((c) => {
      if (!c) return;
      setTitle(c.title);
      setDetails(c.details);
      setDate(new Date(c.dateISO));
      setSolved(c.solved);
      setPhotoUri(c.photoUri);
    });
  }, [id]);

  const onPickPhoto = async () => {
    const res = await ImagePicker.launchImageLibraryAsync({
      mediaTypes: ImagePicker.MediaTypeOptions.Images,
      quality: 0.7,
      allowsMultipleSelection: false,
      selectionLimit: 1,
    });
    if (!res.canceled && res.assets?.[0]?.uri) {
      setPhotoUri(res.assets[0].uri);
    }
  };

  const onSave = async () => {
    const payload: Crime = {
      id,
      title: title.trim(),
      details: details.trim(),
      dateISO: date.toISOString(),
      solved,
      photoUri,
    };
    await upsertCrime(payload);
    Alert.alert("Saved", "This crime was uploaded successfully.");
  };

  return (
    <SafeAreaView style={[S.screen, { padding: 12 }]}>
      <View style={{ flexDirection: "row", gap: 12, alignItems: "flex-start" }}>
        <View style={{ width: 72, alignItems: "center" }}>
          {photoUri ? (
            <Image
              source={{ uri: photoUri }}
              style={{ width: 72, height: 72, borderRadius: 8 }}
            />
          ) : (
            <View
              style={[
                S.card,
                {
                  width: 72,
                  height: 72,
                  justifyContent: "center",
                  alignItems: "center",
                },
              ]}
            ></View>
          )}
          <View style={{ height: 8 }} />
          <Pressable
            style={[S.button, { paddingVertical: 8, width: 72 }]}
            onPress={onPickPhoto}
            accessibilityLabel="Pick Photo"
          >
            <Ionicons name="camera-outline" size={18} color={theme.text} />
          </Pressable>
        </View>

        <View style={{ flex: 1, gap: 10 }}>
          <Text style={[S.text]}>Title</Text>
          <TextInput
            value={title}
            onChangeText={setTitle}
            placeholder="Enter title"
            placeholderTextColor={theme.text + "88"}
            style={S.input}
          />
        </View>
      </View>

      <View style={{ height: 12 }} />

      <Text style={[S.text]}>Details</Text>
      <TextInput
        value={details}
        onChangeText={setDetails}
        placeholder="What happened?"
        placeholderTextColor={theme.text + "88"}
        style={[S.input, { minHeight: 90, textAlignVertical: "top" }]}
        multiline
      />

      <View style={{ height: 12 }} />

      <View
        style={{
          flexDirection: "row",
          alignItems: "center",
          justifyContent: "space-between",
        }}
      >
        <Pressable
          style={[S.button, { flex: 1, marginRight: 8 }]}
          onPress={() => setDateOpen(true)}
        >
          <Text style={S.buttonText}>{date.toDateString()}</Text>
        </Pressable>

        <View
          style={{ flexDirection: "row", alignItems: "center", marginLeft: 8 }}
        >
          <ExpoCheckbox
            value={solved}
            onValueChange={setSolved}
            color={solved ? theme.tint : undefined}
          />
          <Text style={[S.text, { marginLeft: 6 }]}>Solved</Text>
        </View>
      </View>

      <View style={{ height: 16 }} />

      <Pressable style={S.button} onPress={onSave}>
        <Text style={S.buttonText}>Save</Text>
      </Pressable>

      <Modal
        visible={dateOpen}
        transparent
        animationType="fade"
        onRequestClose={() => setDateOpen(false)}
      >
        <View
          style={{
            flex: 1,
            backgroundColor: "#00000066",
            justifyContent: "center",
            padding: 24,
          }}
        >
          <View
            style={[
              { padding: 16, borderRadius: 12 },
              { backgroundColor: theme.card },
            ]}
          >
            <Text style={[S.text, { fontWeight: "600", marginBottom: 8 }]}>
              Pick Date
            </Text>
            <DateTimePicker
              value={date}
              mode="date"
              display={Platform.OS === "ios" ? "spinner" : "calendar"}
              onChange={(_, d) => {
                if (d) setDate(d);
              }}
            />
            <View
              style={{
                flexDirection: "row",
                justifyContent: "flex-end",
                marginTop: 8,
                gap: 12,
              }}
            >
              <Pressable onPress={() => setDateOpen(false)}>
                <Text style={[S.text, { color: theme.tint }]}>Done</Text>
              </Pressable>
            </View>
          </View>
        </View>
      </Modal>
    </SafeAreaView>
  );
}
