import struct
import serial
import time

def main():
    try:
        address = '/dev/ttyACM0'
        ser = serial.Serial(address)
    except FileNotFoundError:
        print(f'Cant connect to {address}')
        exit(1)
        
    start_time = int(time.time() * 1000)
    interval = 1000
    setpoint_bluepill_1 = "1000\n"
    counter = 0

    while True:
    #     response = ser.readline()
    #     decoded_response = response.decode('ASCII')
    #     
    #     print(decoded_response)

        current_time = int(time.time() * 1000)
        elapsed_time = current_time - start_time
        
        ser.write(setpoint_bluepill_1)
        #response = ser.read(4)  # Читаем 4 байта, так как float состоит из 4 байтов
        #if len(response) == 4:
            # Распаковываем байты в float
            #decoded_response = struct.unpack('f', response)[0]
            #print(decoded_response)
            
            
        if elapsed_time >= 3000 and elapsed_time < 6000 and counter == 0:
            setpoint_bluepill_1 = "200\n"
            print(setpoint_bluepill_1)
            counter += 1

        if elapsed_time >= 6000 and elapsed_time < 9000 and counter == 1:
            setpoint_bluepill_1 = "450\n"
            print(setpoint_bluepill_1)
            counter += 1

        if elapsed_time >= 9000 and elapsed_time < 12000 and counter == 2:
            setpoint_bluepill_1 = "100\n"
            print(setpoint_bluepill_1)
            counter += 1

        if elapsed_time >= 12000 and counter == 3:
            setpoint_bluepill_1 = "300\n"
            print(setpoint_bluepill_1)
            counter = 0
            start_time = current_time

if __name__ == "__main__":
    main()