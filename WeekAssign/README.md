There are a number of elements in this demo program that do not perform as they would in the final version. The most substantial of these are the following:
Login Credentials:
In the demo program, login information is pre-defined in the source code with no options to modify or secure this data. A production version of this software would include proper password encryption as well as options for changing user ids and passwords.

Home Menu:
The home menu frequently displays "home >" twice instead of once. The bug is known and being actively pursued, but has not yet been resolved.
Data Storage:
The demo program stores all account data in an internal object that serves as a hybrid database/interface. If advanced to a production verion, a proper database system would be implemented, and the current hybrid object would be converted to a pure interface object such that any existing calls to its members or member functions would retain identical returns to minimize the impact of transition.
Additionally, the demo program does not retain any data between uses. This would be a critical failure in a production version, and will be remedied as part of the database integration should the project move forward.

New Accounts:
A new account is refused as pre-existing if either the name or the social security numbers match an existing account, as this was the interpretation taken from the specification. Should different behavior be desired, it would be simple to implement;
The date attached to all new accounts is hard-coded in the demo version due to development time constraints. Future versions, especially any production version, would properly query system time/date before converting it to an appropriate format to append to the new account.