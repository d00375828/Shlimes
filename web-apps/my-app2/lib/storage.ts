import AsyncStorage from "@react-native-async-storage/async-storage";

export type Crime = {
  id: string;
  title: string;
  details: string;
  dateISO: string;     
  solved: boolean;
  photoUri?: string;   
};

const KEY = "crimes_v1";

export async function loadCrimes(): Promise<Crime[]> {
  try {
    const s = await AsyncStorage.getItem(KEY);
    if (!s) return [];
    const data = JSON.parse(s) as Crime[];
    if (!Array.isArray(data)) return [];
    return data;
  } catch {
    return [];
  }
}

export async function saveCrimes(crimes: Crime[]): Promise<void> {
  await AsyncStorage.setItem(KEY, JSON.stringify(crimes));
}

export async function getCrime(id: string): Promise<Crime | null> {
  const all = await loadCrimes();
  return all.find(c => c.id === id) ?? null;
}

export async function upsertCrime(c: Crime): Promise<void> {
  const all = await loadCrimes();
  const i = all.findIndex(x => x.id === c.id);
  if (i >= 0) all[i] = c; else all.push(c);
  await saveCrimes(all);
}

export function uuid(): string {
  const s: string[] = [];
  for (let i = 0; i < 36; i++) {
    if (i === 8 || i === 13 || i === 18 || i === 23) { s[i] = "-"; continue; }
    const r = Math.floor(Math.random() * 16);
    s[i] = (i === 14 ? 4 : (i === 19 ? (r & 0x3) | 0x8 : r)).toString(16);
  }
  return s.join("");
}

// To clear all crimes for testing
export async function clearCrimes(): Promise<void> {
    await AsyncStorage.removeItem("crimes_v1"); // same key as saveCrimes/loadCrimes
  }