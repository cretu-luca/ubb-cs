using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.SignalR;
using WebApplication5;
using WebApplication5.Hubs;
using WebApplication5.Model;

namespace MyApp.Namespace
{
    public class ReserveModel : PageModel
    {
        private readonly AppDbContext _context;
        private readonly IHubContext<ReservationHub> _hubContext;
        public List<HotelRoom> Rooms { get; set; }
        public int percentageToAdd { get; set; }
        public String message { get; set; }

        public ReserveModel(AppDbContext context, IHubContext<ReservationHub> hubContext)
        {
            _context = context; 
            _hubContext = hubContext;
            Rooms = new List<HotelRoom>();
        }
        
        public void OnGet()
        {
            
        }

        public void OnPostLoadRooms()
        {
            Console.WriteLine("am intrat aici");
            
            DateTime checkInDate = DateTime.Parse(Request.Form["checkInDate"]);
            DateTime checkOutDate = DateTime.Parse(Request.Form["checkOutDate"]);
            int guests = int.Parse(Request.Form["guests"]);
            
            HttpContext.Session.SetString("checkInDate", checkInDate.ToString());
            HttpContext.Session.SetString("checkOutDate", checkOutDate.ToString());
            HttpContext.Session.SetInt32("guests", guests);
            
            List<HotelRoom> allRooms = _context.HotelRooms.Where(r => r.Capacity >= guests).ToList();
            List<Reservation> reservations = _context.Reservations.ToList();

            int numberOfReservations = 0;
            int numberOfRooms = allRooms.Count;

            foreach (Reservation reservation in reservations)
            {
                if (!(checkInDate > reservation.CheckOutDate || checkOutDate < reservation.CheckInDate))
                {
                    allRooms = allRooms.Where(r => r.Id != reservation.RoomId).ToList();
                    numberOfReservations++;
                }
            }
            
            int perc; 
            
            if (numberOfReservations != 0)
            {
                perc = numberOfRooms / numberOfReservations;
                if (perc <= 0.5)
                {
                    percentageToAdd = 0;
                } 
                else if (perc <= 0.8)
                {
                    percentageToAdd = 20;
                }
                else
                {
                    percentageToAdd = 50;
                }
            }
            else
            {
                percentageToAdd = 0;
            }
            
            Rooms = allRooms;
        }

        public async Task<IActionResult> OnPostReserveClicked()
        {
            message = "";
            int roomId = int.Parse(Request.Form["id"]);
            HotelRoom room = _context.HotelRooms.FirstOrDefault(r => r.Id == roomId);
            
            DateTime checkInDate = DateTime.Parse(HttpContext.Session.GetString("checkInDate"));
            DateTime checkOutDate = DateTime.Parse(HttpContext.Session.GetString("checkOutDate"));
            int guests = (int) HttpContext.Session.GetInt32("guests");
            
            // Check if this room is already booked for the requested period
            List<Reservation> roomReservations = _context.Reservations.Where(r => r.RoomId == roomId).ToList();
            foreach (Reservation reservation in roomReservations)
            {
                if (!(checkInDate > reservation.CheckOutDate || checkOutDate < reservation.CheckInDate))
                {
                    message = "Room already booked for these dates";
                    return Page();
                }
            }
            
            // Check if user already has bookings for the requested period
            int userId = (int)HttpContext.Session.GetInt32("id");
            List<Reservation> userReservations = _context.Reservations.Where(r => r.UserId == userId).ToList();
            foreach (Reservation reservation in userReservations)
            {
                if (!(checkInDate > reservation.CheckOutDate || checkOutDate < reservation.CheckInDate))
                {
                    message = "You already have a reservation for this period";
                    return Page();
                }
            }

            if (message == "")
            {
                Reservation reservationToAdd = new Reservation();
                reservationToAdd.CheckInDate = checkInDate;
                reservationToAdd.CheckOutDate = checkOutDate;
                reservationToAdd.RoomId = roomId;
                reservationToAdd.NumberOfGuests = guests;
                reservationToAdd.UserId = userId;
                reservationToAdd.TotalPrice = room.BasePrice + room.BasePrice * percentageToAdd / 100;

                _context.Add(reservationToAdd);
                _context.SaveChanges();
                
                // Send notification to all other users
                string notificationMessage = $"New reservation created for Room {room.RoomNumber} from {checkInDate.ToShortDateString()} to {checkOutDate.ToShortDateString()}";
                await _hubContext.Clients.Others.SendAsync("ReceiveNotification", notificationMessage);
            }

            return Page();
        }
    }
}
