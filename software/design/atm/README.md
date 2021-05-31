# README

## Requirments

![Requirements](images/20210415_005545.png)

* Operator: The operator will be responsible for the following operations:
  * Turning the ATM ON/OFF using the designated Key-Switch
  * Refilling the ATM with cash
  * Refilling the ATM’s printer with receipts
  * Refilling the ATM’s printer with INK
  * Take out deposited cash and checks

* Customer: The ATM customer can perform the following operations:
  * Balance inquiry: the user can view his/her account balance
  * Cash withdrawal: the user can withdraw a certain amount of cash
  * Deposit funds: the user can deposit cash or checks
  * Transfer funds: the user can transfer funds to other accounts

* Bank Manager: The Bank Manager can perform the following operations:
  * Generate a report to check total deposits
  * Generate a report to check total withdrawals
  * Print total deposits/withdrawal reports
  * Checks the remaining cash in the ATM

## Diagram

![Class Diagram](images/20210415_005639.png)

![Sequence Diagram](images/20210415_010013.png)

## MVC Pattern

![mvc](images/20210219_190939.png)

* View: Handle rendering logic
* Controller: Handle user input logic
* Model: Service logic for bank account
* Database: JsonDB stores data in local db

* Sample main loop logic

```py
from main import Status
from model import create_model
from view import create_view
from controller import create_controller

VIEW_TYPE = "CONSOLE"
CONTROLLER_TYPE = "CONSOLE"
MODEL_TYPE = "MEMORY"

model = create_model(MODEL_TYPE)
view = create_view(VIEW_TYPE, model)
controller = create_controller(CONTROLLER_TYPE, model)

view.show_option(model.status)

while not Status.OVER:
  command = input()
  controller.run(command())
  view.run()
```

* Sample data

```json
{"user_id": "sean", "hashed_pin_id": "99fb2f48c6af4761f904fc85f95eb56190e5d40b1f44ec3a9c1fa319", "balance": 0}
```
