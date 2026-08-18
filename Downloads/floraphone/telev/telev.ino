// Пин, к которому подключен электрод А0
const int plantPin = A0; 
// Пин для подключения пьезодинамика (динамика)
const int buzzerPin = 9; 

// Переменные для сглаживания сигнала
int sensorValue = 0;
int smoothedValue = 0;

void setup() {
  Serial.begin(9600); // Запуск монитора порта для проверки
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Считываем значение с растения (от 0 до 1023)
  sensorValue = analogRead(plantPin);
  
  // Сглаживаем сигнал (фильтр бегущего среднего)
  smoothedValue = (smoothedValue * 0.9) + (sensorValue * 0.1);
  
  // Выводим данные в компьютер, чтобы видеть реакцию
  Serial.print("Биосигнал: ");
  Serial.println(smoothedValue);

  // Переводим значения датчика в диапазон звуковых частот (в Герцах)
  // Если звук слишком высокий или низкий, измените числа 200 и 1000
  int frequency = map(smoothedValue, 100, 900, 200, 1000);

  // Если сигнал стабильный и растение "молчит", не шумим
  if (smoothedValue > 50) {
    tone(buzzerPin, frequency, 80); // Воспроизводим звук длительностью 80 мс
  } else {
    noTone(buzzerPin);
  }

  delay(100); // Пауза между «нотами»
}
