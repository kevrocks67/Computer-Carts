# Computer-Carts
 A python3 based project built on a kivy gui and sql database in order to manage the laptop carts at the Columbia Secondary School.

## Project Author
  Kevin Diaz

## Motivation and Story
   During my time at the Columbia Secondary School, I worked closely with the IT department helping in any way I could. One of the things I frequently had to do was move the laptop carts from one room to another at the end of a certain period. This was where I realized that there was a problem which needed solving. Frequently, our "tech team" had to rely on the instruction of the head of the IT department to tell us what to do. Sometimes even he didn't know which cart had to go to which room at what time. Another problem which existed was that the carts were typically left unlocked overnight since the head was the only one who had the keys to the carts. As a security freak myself, this did not bode well with me. After having searched for a project to work on for several months, the opportunity to take on this problem arised. I decided to create this application as part of my Capstone Engineering Final Project.
  
  
   I spent approximately 3 weeks trying to think about all the systems I would need to discover and how I was going to integrate them all together. I began searching on the internet for other management softwares people have made for other purposes and learned that a lot of them were designed in visual basic. I knew that regardless of what language I chose to work with, I would have to learn it in a timely matter. I decided to try this method since it seemed easy on video and was able to easily communicate with SQL which was the only kind of database I was familiar with at the time. I needed SQL because of my locking and unlocking solution which will be explained later. So I attempted to start off my app by creating a ~~simple~~ combobox. It was one of the most annoying things I have ever done and guess what... after 3 weeks of researching and attempting different solutions and even pre-written code, I could not get it to work. At this point I began searching for alternatives. Time was starting to run out and I knew this would be a time consuming project. I knew for a fact that I was not going to develop in java because well, I have developed an android application before and java did not like to cooperate much which I did not have time for. I then remembered hearing that python was an easy language to learn but extremely versatile. I did not know much about python at all. In fact, at the time I thought it was just another dumb teaching tool like scratch where sure it gets it done but you didnt actually do much. Boy was I wrong. Over this project I have learned to love python and appreciate just how useful it is in all realms of the world.
  
  
   Now that I had chosen a programming language I had to figure out how to make a gui appliation using python. I began doing research and for some reason I was attracted to kivy. I believe I had seen the website before and it looked cool. Keep in mind, at this time I did not understand that tkinter, pyqt and wxpython were really useful tools and tkinter came with python. This really annoyed me when I figured all of this out approximately 2 months before the deadline. Lets just say, kivy did not like to play nice. I spent a week trying to install it because I kept getting different dependency errors which I could not fix despite doing as instructed. Once I finally got it installed, I began looking at example code and reading the starters guide. I attempted to remake the pong app without copy and pasting the code. My thought process was, if im going to learn this syntax, I need to actually type it myself. I struggled with that a lot which really annoyed me since at this point I had been failing to put out anything at all for about 2 months. I finally got the hang of indentations, capitalization, the syntax, and general structure of kivy and python and work on the app was on its way. I had created an action bar and various screens which were layed out but not functioning, meaning text input boxes which did not have any code applied to them. At this point it was time to begin to work on the meat of the application which was retrieving information from the SQL server and displaying it. In my head I knew what I wanted, but when doing research, not much showed up. I attempted to figure out this kivy widget called ListView and figured it out in about 2 weeks. Turns out that 3 days after I figure it out and displayed the items from the database successfully, kivy updated releasing a new widget called RecycleView and deprecating ListView.So... there goes kevin's hopes and dreams...again. RecycleView was exactly what I needed and what I envisioned but, it was so new, and still is, that there was barely any documentation on it. I worked off of 2 very basic example scripts and built what I wanted. Long story short, or longer story less long, I ended up finishing the app in sqlite3 in order to be able to send the code to my teacher without him having to set up an sql server. I created a login screen which stores the password as a salted hash (sha-512) in a config file locally not because a login is necessary for this app but because I had been learning about cybersecurity on the side of all this and had to attempt to implement some security.
  
  
   The app is functioning as well as I can get it in the time alloted. I made the login screen look nice with toast messages, which I borrowed the code from Segreto3 app here on github. There was no time left for the unlock/lock feature so this is not working. Another feature that is missing is the implementation of an email notification system. It sits in the settings screen, but is currently not working. I attempted to compile the app into an exe with PyInstaller, but for some reason RecycleView does not want to compile with it. Because of this the app is only available on here as raw code. Overall, this project has been a great learning experience. It has opened my eyes to the world of programming and allowed me to realize how much fun it can be, unlike my other experiences with it. I now walk away with a skill in a highly needed programming language *python* as well as *sql* and *kivy*.
  
  
### Python Requirements for mySQL version:
    Kivy
    pymysql
    Running SQL server using table creation method in "Database Files" folder
    
    
### Python Requirements for SQLITE3 version:
    Kivy
    
    
## Setup for absolute beginner (Windows)
  1. Download and install python 3 from (https://www.python.org/ "Python's Homepage") and make sure you allow it to create a PATH.
  2. If you let the installer create a PATH, then you must install Cython, a pre-requisite for kivy. Type in
  
  
  `python -m pip install cython`
  3. Now install kivy by typing
  `python -m pip install kivy`
  4. Download the github project and open the Computer Cart SQLITE folder
  5. Find and open the ComputerCartClientSQLITE3.py file in Idle which was installed with python (*try double clicking the file*).
  6. Register an account and login
  7. Have fun adding, removing, and editing computer carts!

## Design Process

**A diagram I drew on a handout during english class:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Mockup%20Designs/EPSON010.JPG "diagram")

**Pseudocode I created while designing the login screen:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Mockup%20Designs/EPSON011.JPG "diagram")

**Main Screen Mockup MSPaint:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Mockup%20Designs/Main%20Screen%20Mockup%20Design.png "Main Screen Mockup MSPaint")

**Edit Screen Mockup MSPaint:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Mockup%20Designs/Edit%20Button%20Pop%20Up%20Mockup%20Design.png "Edit Screen Mockup MSPaint")

**Settings Screen Mockup MSPaint:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Mockup%20Designs/Settings%20Pop%20up%20Mockup%20Design.png "Settings Screen Mockup MSPaint")

## Screenshots
Login Screen With Toast from Segreto3:


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Screenshots/login%20with%20toast.PNG "Login Screen With Toast from Segreto3")

**Main Screen:**

![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Screenshots/main%20screen.PNG "Main Screen")

**Add Function Selected:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Screenshots/main%20screen%20with%20add%20cart.PNG "Add Function")

**Settings Screen:**


![alt text](https://github.com/kevrocks67/Computer-Carts/blob/master/Screenshots/settings.PNG "Settings Screen")


## Video

To be uploaded

## License
    kevrocks67/Computer-Carts
    Copyright (C) <2017>  <Kevin Diaz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
