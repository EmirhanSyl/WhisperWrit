# WhisperWrit
 WhisperWrit Online Letter Delivery Services


### Aim of The Project

The online letter delivery system aims to create a user-friendly and efficient platform that enables users to send and receive digital letters, resembling traditional mail but in a digital format. This system seeks to provide a seamless and secure communication experience, allowing users to compose, send, and receive letters within a virtual environment. By bridging the gap between the charm of physical letters and the convenience of digital communication, the project aims to offer a nostalgic yet modernized approach to personal and professional correspondence in an online setting.

### Program Structs and Relationships

2.1) The main purpose of use of person struct:
- The person struct represents users in OOP way. Letter senders and receivers information holds in person structs.
2.2) The main purpose of use of letter struct:
- letter struct represents real-life letters. This struct holds message, subject and id.
- When user send or create letter, this struct will be initilized by system.
2.3) The main purpose of use of post struct: 
- The post struct represents deliverity of letters. This struct holds letter’s sender, receiver, status etc. 
- This struct connects letters and users each other. 
2.4) The main purpose of use of database.c file:
- This file manages all file API integrations. (Read, write, update, delete)

### 3. Rules:
Initially, 2 users, 3 sent letter and 2 template letter are defined in the system by default. You can access the user information from the person.txt file.

#### 3.3) Program Features:
- Users can create account and login
- Users can send letter to any other user.
- Users can receive letters from anyone, list received letters and read them
- Users can list template letters, edit them and send again.
- Users can delete template letters
- Users can show contact list

3.3) Complex Rules:
- When the receiver read his/him letter, letter statue will be ‘SEEN’. And sender can see if receiver read his letter or not.
- User can create template letters without sending them. Then they can select template letter and send them to anyone in any mode.
- Sender can send letter in 2 ways: ‘NORMAL’ and ‘WHISPER’
- Whisper Mode: This mode ensures extra security and private messaging. When receiver reads letters that send with this mode, letter and post will be deleted from database forever.
- Normal Mode: This mode is classic messaging. When receiver reads letters that send with this mode, Nothing happens..
