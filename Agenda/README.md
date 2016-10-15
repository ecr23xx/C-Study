# Introduction
**Agenda** is a Meeting manage system. You can creat users and meetings, and manage them as well. 

# Useage
1. Download and compile, and run it directly in console.
2. Your data will be saved in `Agenda/data`.

# Design
We chose the 3 levels structure and [Singleton pattern](https://github.com/ECer23/C-Study/issues/7)
1. First the basic class `User`, `Meeting` and `Date`, which define objects' attribute. And `Storage` defines the basic interaction between data and program.
2. Second the logic object `AgendaService`, every action is implemented by `AgendaService`.
3. Last the client level `AgendaUI`.