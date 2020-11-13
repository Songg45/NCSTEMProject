# NCSTEMProject

This repository is the code used in my NC STEM Alliance project. This will be a Vehicle to Everything (V2X) communication platform, specifcally to communicate a vehicle's speed and location to an Android device. This project will be made in 6 phases over 2 years:

YEAR 1 -

   Phase 1:
   
         Build UDP server/client to communicate via broadcast messages on an 802.11 network - COMPLETED
        
   Phase 2:
   
         Use ECU simulator to send a simulated vehicle's speed and an arbitrary GPS coordinate out via UDP broadcast
        
   Phase 3:
   
         Have receiver determine its location, and determine if the sender is approaching using its GPS coordinates 
         and speed. If receiver determines that the sender is approaching, display an alert.
        
YEAR 2 -

   Phase 4:
   
         Move network from 802.11 to 5.9GHz like the FCC intended
        
   Phase 5:
   
         Build a dedicated SOC (System On Chip) for car's communication
        
   Phase 6:
   
         Allow the use of multiple sender and receivers. Fully implemented solution at this point.
