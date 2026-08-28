# DS FERRIES — Documentation

**Course:** Programming Language C — University of Piraeus, Dept. of Digital Systems
**Assignment:** 2nd Mandatory Project, Winter Semester 2023–2024
**Project:** Ferry Ticket Booking System for "DS Ferries"

## Table of Contents

1. [Introduction](#introduction)
2. [User Manual](#user-manual)
3. [Future Improvements](#future-improvements)
4. [User-Defined Function Reference](#user-defined-function-reference)

## Introduction

This document is a concise manual for the DS FERRIES application, describing how to use each of its features. The functionality included in this version is:

1. Creation of multiple users & storage of their details.
2. Viewing of available routes.
3. Selecting a seat type & booking it.
4. Option to include a vehicle.
5. Option for a one-way or round trip.
6. Viewing unconfirmed (unpaid) bookings.
7. Sorting confirmed bookings in ascending or descending calendar order.

## User Manual

### Main Screen

On launch, the program shows the main menu:

- `1` → Sign Up: goes to the new-user registration screen.
- `2` → Login: goes to the login screen.
- `0` → Exit the program.

### Sign Up

Provided fewer than 30 clients are already registered, the user enters the requested details:

- Must be **18 or older**.
- Card number must be a valid **16-digit** number.
- Password must be exactly **7 characters**.
- University students get a **50% discount** on total trip cost.
- Username must be unique.

### Login

Using the username and password chosen at sign-up, the user logs in to book a trip. A user cannot log in without first signing up.

### User Dashboard

After a successful login, the user chooses among five options. After completing any option (except Logout), control returns to this dashboard.

- **a — View Available Routes:** lists all destinations, seat types, and vehicle surcharge.
- **b — Book Trip:** the user picks a departure date, destination (by port code), seat type (Deck / Airplane Type / Cabin), whether to include a vehicle, and whether the trip is one-way or round trip (entering a return date if so). A new booking's date must fall after the end date of the user's previous booking. Cost is calculated as:
  - `Initial Trip Cost = Seat Cost (by destination & seat type) + Vehicle Surcharge (if any)`
  - `Return Trip Cost = 0.75 × Initial Trip Cost` (if round trip)
  - `Total Cost = Initial Trip Cost + Return Trip Cost`, halved if the user is a student.
  - A unique **Trip ID** is generated as `DDMMYYYY` of the departure date + port code + `-` + username (e.g. `28022024KOS-sonem`).
- **c — Payment:** available only if the user has at least one unpaid ("PENDING") booking. Lists all pending bookings; the user enters a Trip ID to confirm payment. Invalid or already-paid IDs prompt an error and re-entry.
- **d — Confirmed Trips:** available only once the user has at least one "CONFIRMED" booking. The user can sort confirmed trips by departure date, `HIGH` (ascending) or `LOW` (descending).
- **e — Logout:** returns to the main screen.

## Future Improvements

- Increase the maximum number of stored users and allow more than 50 trips per user.
- Allow booking of trips whose dates overlap with existing ones.
- Allow changing seat type or vehicle choice for the return leg of a round trip.
- Confirm a booking using the card number as well as the Trip ID.
- Enforce stronger passwords (require special characters and digits).
- Add a surcharge for oversized vehicles (>4.5 m).
- Support additional vehicle types: motorcycle, caravan, truck, trailer/boat trailer.
- Add discounted fares for more special categories (e.g. people with disabilities).

## User-Defined Function Reference

| Function             | Parameters                        | Return type |
| -------------------- | --------------------------------- | ----------- |
| `user_signup()`      | `void`                            | `void`      |
| `get_new_user()`     | `void`                            | `void`      |
| `username_exists()`  | `char answer_username[20]`        | `int`       |
| `user_login()`       | `int p`                           | `void`      |
| `check_login()`      | `void`                            | `int`       |
| `input_routes()`     | `void`                            | `void`      |
| `view_routes()`      | `void`                            | `void`      |
| `book_trip()`        | `int p`                           | `void`      |
| `compare_trips()`    | `int p, int sygkekrimeno_taksidi` | `int`       |
| `generate_trip_id()` | `int p`                           | `void`      |
| `payment()`          | `int p`                           | `void`      |
| `confirmed_trips()`  | `int p`                           | `void`      |
