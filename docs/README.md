
#### Dock: Unlock
GET *http://peraride-api.herokuapp.com/api/auth/dock/unlock?dock_id=1111.1*

When user pressed the unlock button, this is the API request send by the Docking station controller to the server.

##### Parameters
- dock_id

##### Response
- Access Granted (200)
```
{
    "message": "Access Granted"
}
```
- Access Denied (406)
```
{
    "message": "Access Denied"
}
```

#### Dock: Lock
POST *http://peraride-api.herokuapp.com/api/auth/dock/lock*

Acknowledgement message to inform the server about a bike was attached to a Dock.

##### Body Parameters
```
{
    "dock_id": "1111.1",
    "rfid_code":"asd2324"
}
```

##### Response
- 404
```
{
    "message": "Dock Must be free in order to dock a bike",
    "extra": null,
    "errors": {
        "name": "APIError",
        "message": "Dock Must be free in order to dock a bike",
        "status": 404,
        "extra": null
    }
}
```

Note:
When user didn't un mounted the bike within 30sec, this should be sent by the Station controller to the server.

#### Bike: unlock
GET *http://peraride-api.herokuapp.com/api/auth/bike/unlock?bike_id=10005*

This is the API call send by the mobile app to the server, by asking to unlock a bike

##### Parameters
- bike_id

##### Response  
- 404 if no bike is found with the id or empty query parameter
```
{
    "message": "No bike associated with Bike ID 10003",
    "extra": null,
    "errors": {
        "name": "APIError",
        "message": "No bike associated with Bike ID 10003",
        "status": 404,
        "extra": null
    }
}
```

- 200 if bike exists and now bike resource locked for 30 seconds for the user. If user does
```
{
    "bike_id": 10001,
    "rfid_code": "85555FA5",
    "state": "AVAILABLE",
    "bike_secret": 10001,
    "dock_id": 1111.2,
    "current_user": "5fddeeab88a9f30004d07ddb",
    "resourceLock": true
}
```

Note: If not pressed the button in the dock within this 30 seconds, resource lock will be cleared.
If another user request for the same bike within this 30 seconds ?
