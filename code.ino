#include "DHT.h"
#include <TimeLib.h>

#define DHTPIN 2                         // Pin number to connect DHT11 on Arduino (It can be any digital IO pin) / DHT11 'in Arduino üzerinde bağlanacağı pin numarası (Herhangi bir digital IO pini olabilir )
#define DHTTYPE DHT11                    // To determine the model of our DHT (Since the library written for DHT22 and its derivatives is DHT11, we will use it) / DHT mizin modelini belirlemek için (Kütüphane DHT22 ve türevleri için yazılmış bizim kullanacağımız DHT11 olduğu için bunu oluşturuyoruz)
unsigned long DEFAULT_TIME = 1622287190; // https://www.epochconverter.com/ From here we can get the current time and paste it (it's very easy for TimeLib to get it as Epoc time and parse it) / https://www.epochconverter.com/ Buradan şimdiki zamanı alıp yapıştırabiliriz (Epoc time olarak alıp parse etmek TimeLib için çok kolay)
DHT dht(DHTPIN, DHTTYPE);                // We create our DHT sensor's object /  DHT sensörümüz için  objemizi oluşturuyoruz

String commonFunction() // This function is where we read all the values and return a string in accordance with the printing style of all of them. Here below functions are called for different temperature values for 'day' and 'night'. / Bu fonksiypn tüm değerlerin okunup hepsinin bastırım şekline uygun olarak bir string dööndürdüğümüz yer burda 'day' ve 'night' için farklı sıcaklık değerleri için aşağıda fonskiyonlar çağrılmakta
{
    int humidityValue = dht.readHumidity();       // Read humidity / Nemi okuyoruz
    int ldrValue = analogRead(A0);                // Since the value coming from LDR will be analog data, we are reading connected to A0 pin (It can be any analog input) / LDR den gelen değer analog veri olacağı için A0 pinine bağlı okuma yapıyoruz (Herhangi bir analog giriş olabilir)
    int temperatureValue = dht.readTemperature(); // We read the temperature value / Sıcaklık değerini okuyoruz
    return " Date: " + makeDouble(day()) + "." + makeDouble(month()) + "." + String(year()) + " - Hour: " + makeDouble(hour()) + ":" + makeDouble(minute()) + " - Light: " + String(ldrValue) + " Temperature: " + String(temperatureValue) + " Humidity: " + String(humidityValue) + "%\n" +
           DayCatagory(ldrValue) + " - " + Day(DayCatagory(ldrValue), temperatureValue) + " - " + humidity(humidityValue); // // Here is the part where we return the desired message to be suppressed /  Burada bastırılması istenen mesajı döndürdüğümüz kısım
}
String makeDouble(int param) //The function that I wrote in the previous lab that allows us to add 0 in the beginning if the hours and days are less than 10 /  Bir önceki lab da yazdığım , saat ve günlerin 10 dan küçük olması durumunda başına 0 eklememizi sağlayan fonksiyon
{
    if (param < 10)
        return "0" + String(param);
    return String(param);
}
String humidity(int humidityValue) // The function for returning the conditions according to the state of humidity / Nemin durumuna göre olan koşulların döndürüldüğü fonksiyon
{
    if (humidityValue < 30)
        return "Low humidity";
    else if (humidityValue > 50)
        return "High humidity";
    return "Optimal humidity";
}

String DayCatagory(int ldrValue) // // Our function that returns 'day' and 'night' according to the value read from the LDR / LDR'den okunan değere göre 'day' veya 'night' döndüren fonksiyonumuz
{
    if (ldrValue >= 400)
        return " Day ";
    return " Night ";
}
String Day(String day, int temperatureValue) // Optimum temperatures vary depending on whether the day is 'day' or 'night'. / Günün 'day' mi 'night' mı olmasına göre optimum sıcaklıklar değişmekte onun kontrolünü yapan fonksiyonumuz
{
    int min, max;      // min and max values are different in the morning and evening. / min max değerleri sabah ve akşam farklı
    if (day[1] == 'D') // According to the value of the ldr we call day, the string variable, which we return day or night, is the value returned in the above function; if its 1st index is D it is 'Day' otherwise it is 'Night' / day dediğimiz ldr'nin değerine göre gün mü gece mi olduğunu döndürdüğümğz string değişkeni yukarıdaki fonksiyonda dönen değer ; eğer bunun 1. indexi D ise 'Day' dir eğer değilse 'Night' tır
    {
        min = 20; // If it is 'Day', I assign the values that the temperature will be cold and hot. / Eğer 'Day' ise sıcaklığın soğuk ve sıcak olacağı değerlerin atamasını yapıyorum
        max = 24;
    }
    else
    {
        min = 18; // If it is 'Night', I assign the values that the temperature will be cold and hot. / Eğer 'Night' ise sıcaklığın soğuk ve sıcak olacağı değerlerin atamasını yapıyorum
        max = 21;
    }
    if (temperatureValue > max) // Checking the hotness or not here / Burada sıcak olma durumunu kontrol ediyorum
    {
        return "Hot";
    }
    else if (temperatureValue < min) // The state of being cold here  / Burada soğuk olma durumunu
    {
        return "Cold";
    }
    return "Optimal Temperature"; // If this is not in 2 cases, I return this to the optimal by saying it is directly here / Bu 2 durumda değilse direk buradadir diyerek bunu optimali döndürüyorum
}
void setup()
{
    Serial.begin(9600); // I initiate communication to press the serial port display / Seri port ekranına bastırmak için iletişimi başlatıyorum
    pinMode(A0, INPUT); // I initialize analog input value / Analog giriş değerini başlatıyorum
    dht.begin();        // I don't need to specify the pinMode for which digital pin will be reading specifically for DHT. Dht.begin sets and starts everything. / DHT için özel olarak hangi dijital pinden okuma yapacaksa onun pinMode şeklinde belirtmeme gerek yok dht.begin tüm her şeyi ayarlıyor ve başlatıyor
}
void loop()
{
    setTime(DEFAULT_TIME);            // I set the variable that we added above as epoch time as the Arduino's clock. (At the same time, we update the incremental time). / Yukarıda epoch time olarak eklediğimiz değişkeni Arduino'nun saati şeklinde ayarlıyorum (Aynı zamanda artan zamanın güncellemesini yapıyoruz)
    Serial.println(commonFunction()); // Here, the desired string value is printed on the screen by returning this function. / Burada Bastırılması istenen string değeri bu fonksiyon return edilerek ekranda bastırılıyor
    DEFAULT_TIME = DEFAULT_TIME + 3;  // I increase the time by 3 seconds / Zamanı 3 saniye arttırıyorum
    delay(3000);                      // We expect 3 seconds to pass / 3 saniye geçmesini bekliyoruz
}

/* Referances 

for Turkish 
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf DHT11 için 5K direnç bağlıyacağımızı ve pinleri gösteren datasheet
https://components101.com/sensors/dht11-temperature-sensor DHT 11 PinOut
https://create.arduino.cc/projecthub/rudraksh2008/connecting-ldr-photoresistor-with-arduino-0107b7 LDR Bağlanım örneği için baktığım Kaynak
https://www.youtube.com/watch?v=NxieXXSnJ9U // Epoc Time için danıştığım RTC ile yapılmış bir proje 

for English
https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf Datasheet showing the pins and connecting a 5K resistor for DHT11
https://components101.com/sensors/dht11-temperature-sensor DHT 11 PinOut
https://create.arduino.cc/projecthub/rudraksh2008/connecting-ldr-photoresistor-with-arduino-0107b7 Source for LDR Connection example
https://www.youtube.com/watch?v=NxieXXSnJ9U // A project made with RTC that I consulted for Epoc Time

*/