#This program helps the user find an average salary for the moon company based off their major and degree accomplished
#Nithya Munagala
#These lines assign each option a number for their salary in list.

careerpath = int(input("Please pick one:\n[1] Computer Science \n[2] Psychology \n[3] Engineering \n[4] Graphic designing \n[5] Finance \n[6] Accounting \n[7] Exit\nPlease enter the field you would like to see the salary of.: "))
print("\n")

#Function returns the modified salary if the user chooses to pursue a masters degree.
def mastersSalary(salary):
    return salary * 1.5

#Function returns the modified salary if the user pursues a doctorate degree.
def phD(salary):
    return salary * 2.0


#Function gives the approximation of salary prospects based on chosen degree and tenure at company.
def Raise(money, years):
    for x in range (0, years):
        money = money * 1.1
    return int(money)



#List holds the base salaries of each major.
salaries = [68000, 40000, 70000, 25000, 50000, 45000]

#This is a while loop which allows the user to type a number in accordance with a selected major as an option, assigning an option to each number
while(careerpath!= 7):

                            #Universal code using the careerpath variable that selects the base salary from the list in accordance with the major
                            degree = int(input("[1] Bachelors\n[2] Masters \n[3] phD\nPlease pick : "))
                            #Calls salary modifier functions to assign salaries by degree 
                            if(degree == 1):
                                    cash = salaries[careerpath-1]
                            if(degree == 2):
                                    cash = mastersSalary(salaries[careerpath-1])
                            if(degree == 3):
                                    cash = phD(salaries[careerpath-1])

                            print("Your salary is: $",cash)

                            print("\n")
                            #Prompts the user to see if they would like to see future salaries if they were to stay at the company.
                            print("\n")
                            answer = int(input("Would you like to see your salary prospects?\n[1]Yes\n[2]No\n"))
                          
                            #Calls raise function and passes salary and years
                            if(answer == 1):
                                noYears = int(input("Input Years of tenure at company\n"))
                                print("Your salary prospect is: \n$",Raise(cash, noYears))
                                
                            print("\n")
                                
                            #Gives the user an option to exit the program, or to explore other major/degree combinations.
                            print("Enter another field, or exit.")
                            careerpath = int(input("[1] Computer Science \n[2] Psychology \n[3] Engineering \n[4] Graphic designing \n[5] Finance \n[6] Accounting \n[7] Exit\n \n: "))
 


#Sucessfully ends the program
print ("Goodbye! Thank you for considering our company, we hope to see you again!")
 
    
