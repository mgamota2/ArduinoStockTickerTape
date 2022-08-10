from yahoo_fin import stock_info
import warnings
import serial
import threading
import time

#Mute pandas future warning from yahoo_fin API
warnings.filterwarnings("ignore", category=FutureWarning) 

#Put the stock names that you want in the stocks list
stocks =['TSLA']


ser = serial.Serial('COM3',9600, timeout=10)


def get_stock_data():
    while True:
        global price
        global stock_change
        global last_price
        global last_stock_change
        stock_change = []
        price = []
        for i in range(0,len(stocks)):
            data=stock_info.get_quote_table(stocks[i])
            current = data.get('Quote Price')
            close = data.get('Previous Close')

            percent = round((((current-close)/close)*100), 2)
            stock_change.append(str(percent))
            price.append(str(round(current, 2)))
            
        last_price = price
        last_stock_change = stock_change
        print(price)
        print(stock_change)

        time.sleep(30)


t = threading.Thread(target = get_stock_data, daemon=True)
t.start()

time.sleep(8)

while True:
    global price
    global stock_change

    for i in range(0,len(stocks)):
        while not ser.inWaiting():
            pass
        if (ser.inWaiting()):
            ser.flushInput()
            print("Ready")
            ser.write(bytes(stocks[i], 'utf-8'))
            print(bytes(stocks[i], 'utf-8'))
            time.sleep(2)
        
            try:
                ser.write(bytes((price[i]), 'utf-8'))
                
                print(bytes(price[i], 'utf-8'))
                time.sleep(1)
            except:
                ser.write(bytes((last_price[i]), 'utf-8'))
                time.sleep(1)
                
            try:
                ser.write(bytes((stock_change[i]), 'utf-8'))
                
                print(bytes(stock_change[i], 'utf-8'))
            except:
                ser.write(bytes((last_stock_change[i]), 'utf-8'))
                

            
