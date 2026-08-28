# DS FERRIES

A console-based ferry ticket booking system for the fictional ferry company DS Ferries, written in C.

## Features

- User sign-up and login with validated credentials (age 18+, 16-digit card number, 7-character password).
- Browse 13 available ferry routes from Piraeus to the Dodecanese, each with Deck / Airplane Type / Cabin pricing and vehicle surcharge.
- Book one-way or round trips, with automatic date-conflict checking against previous bookings.
- Automatic cost calculation, including a 50% student discount and a 25% reduced return-leg fare.
- Unique, auto-generated Trip ID per booking.
- Pay (confirm) pending bookings by Trip ID.
- View confirmed bookings sorted by date, ascending or descending.

## Requirements

- A C compiler such as GCC.
- Windows, since the program uses system("cls") and system("pause"). Swap in system("clear") for Linux/macOS.

## Build and Run

Compile with GCC:

  gcc Index.c -o ds_ferries

Run the resulting binary:

  ./ds_ferries

## Usage

1. From the main menu, choose Sign Up to create an account, then Login.
2. From the User Dashboard, choose one of:
   - a: View available routes
   - b: Book a trip
   - c: Pay for a pending booking
   - d: View confirmed (paid) bookings, sortable by date
   - e: Log out

See documentation.md for a full walkthrough of each screen, the cost formulas, the Trip ID format, and the function reference.

## Project Structure

  .
  Index.c            main program source
  documentation.md   detailed user manual and function reference
  README.md          this file

## Known Limitations

- Maximum of 30 registered users and 50 bookings per user, due to fixed-size arrays.
- Overlapping trip dates are not permitted, even across different destinations.
- Seat type and vehicle choice on the return leg always mirror the outbound leg.
- Password strength is only checked by length, seven characters, not composition.

## Author

Tsirogiannis Efstathios
