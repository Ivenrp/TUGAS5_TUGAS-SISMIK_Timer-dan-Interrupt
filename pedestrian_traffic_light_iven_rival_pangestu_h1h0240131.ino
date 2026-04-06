
//Pin Kendaraan
#define PIN_KEND_MERAH   9
#define PIN_KEND_KUNING  10
#define PIN_KEND_HIJAU   11

//Pin Pedestrian Sisi 1 (kiri) 
#define PIN_PED1_MERAH   12
#define PIN_PED1_HIJAU   13

//Pin Pedestrian Sisi 2 (kanan) 
#define PIN_PED2_MERAH   4
#define PIN_PED2_HIJAU   3

//Pin Tombol
#define PIN_TOMBOL 2

//Durasi
#define DURASI_PEJALAN    5000
#define DURASI_KUNING     2000
#define DEBOUNCE_DELAY    200

//State
volatile bool tombolDitekan = false;
unsigned long waktuTerakhirInterrupt = 0;

void tombolISR() {
  unsigned long sekarang = millis();
  if (sekarang - waktuTerakhirInterrupt > DEBOUNCE_DELAY) {
    tombolDitekan = true;
    waktuTerakhirInterrupt = sekarang;
  }
}

void matikanKendaraan() {
  digitalWrite(PIN_KEND_MERAH,  LOW);
  digitalWrite(PIN_KEND_KUNING, LOW);
  digitalWrite(PIN_KEND_HIJAU,  LOW);
}

void matikanPedestrian() {
  digitalWrite(PIN_PED1_MERAH, LOW);
  digitalWrite(PIN_PED1_HIJAU, LOW);
  digitalWrite(PIN_PED2_MERAH, LOW);
  digitalWrite(PIN_PED2_HIJAU, LOW);
}

void kondisiNormal() {
  matikanKendaraan();
  matikanPedestrian();
  digitalWrite(PIN_KEND_HIJAU,  HIGH);
  digitalWrite(PIN_PED1_MERAH,  HIGH);
  digitalWrite(PIN_PED2_MERAH,  HIGH);
}

void fasePejalanJalan() {
  matikanKendaraan();
  matikanPedestrian();
  digitalWrite(PIN_KEND_MERAH,  HIGH);
  digitalWrite(PIN_PED1_HIJAU,  HIGH);
  digitalWrite(PIN_PED2_HIJAU,  HIGH);
}

void faseTransisi() {
  matikanKendaraan();
  matikanPedestrian();
  digitalWrite(PIN_KEND_KUNING, HIGH);
  digitalWrite(PIN_PED1_MERAH,  HIGH);
  digitalWrite(PIN_PED2_MERAH,  HIGH);
}

void setup() {
  pinMode(PIN_KEND_MERAH,  OUTPUT);
  pinMode(PIN_KEND_KUNING, OUTPUT);
  pinMode(PIN_KEND_HIJAU,  OUTPUT);
  pinMode(PIN_PED1_MERAH,  OUTPUT);
  pinMode(PIN_PED1_HIJAU,  OUTPUT);
  pinMode(PIN_PED2_MERAH,  OUTPUT);
  pinMode(PIN_PED2_HIJAU,  OUTPUT);
  pinMode(PIN_TOMBOL, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_TOMBOL), tombolISR, FALLING);

  kondisiNormal();
  Serial.begin(9600);
  Serial.println("Sistem Traffic Light Pedestrian Siap.");
}

void loop() {
  if (tombolDitekan) {
    tombolDitekan = false;
    Serial.println("Tombol ditekan! Memulai fase pejalan jalan...");

    fasePejalanJalan();
    delay(DURASI_PEJALAN);

    faseTransisi();
    delay(DURASI_KUNING);

    kondisiNormal();
    Serial.println("Kembali ke kondisi normal.");
  }
}