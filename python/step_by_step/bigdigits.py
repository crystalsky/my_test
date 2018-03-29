Zero=['*****','*   *','*   *','*   *','*   *','*   *','*****']  
One=['  *  ',' **  ','* *  ','  *  ','  *  ','  *  ','*****']
Two=['*****','    *','    *','*****','*    ','*    ','*****'] 
Three=['*****','    *','    *','*****','    *','    *','*****']  
Four=['  *  ',' **  ','* *  ','*****','  *  ','  *  ','  *  ']  
Five=['*****','*    ','*    ','*****','    *','    *','*****']  
Six=['*****','*    ','*    ','*****','*   *','*   *','*****']  
Seven=['*****','    *','    *','   * ','  *  ',' *   ','*    ']  
Eight=['*****','*   *','*   *','*****','*   *','*   *','*****']  
Nine=['*****','*   *','*   *','*****','    *','    *','*****']
Digits=[Zero,One,Two,Three,Four,Five,Six,Seven,Eight,Nine]

try:
    digits=input("please input your number:")       #读入数字
    row=0
    while row<7:
        line=""
        column=0
        while column<len(digits):
            number=int(digits[column])
            digit=Digits[number]
            line+=digit[row]+" "
            column+=1
        print(line)
        row+=1
except ValueError as err:
    print(err)


