using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication4;
using WebApplication4.Models;

namespace MyApp.Namespace
{
    public class HotelModel : PageModel
    {
        private readonly AppDbContext _context;
        public ICollection<Hotel> Hotels { get; set; } = new List<Hotel>();

        public HotelModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            List<Hotel> hotels = _context.Hotels.ToList();
            List<Hotel> hotelsWithAvailableRooms = new List<Hotel>();
            
            String destination = HttpContext.Session.GetString("destination");
            String date = HttpContext.Session.GetString("date");

            foreach (Hotel hotel in hotels)
            {
                if (hotel.AvailableRooms > 0 && hotel.City == destination && hotel.Date == date)
                {
                    hotelsWithAvailableRooms.Add(hotel);
                }
            }
            
            Hotels = hotelsWithAvailableRooms;
        }

        public IActionResult OnPost()
        {
            String id = Request.Form["id"];
            
            Hotel hotel = _context.Hotels.Find(int.Parse(id));
            hotel.AvailableRooms -= 1;
            _context.Hotels.Update(hotel);
            
            Reservation reservation = new Reservation();
            reservation.Person = HttpContext.Session.GetString("name");
            reservation.Type = "Hotel";
            reservation.ReservedResourceId = int.Parse(id); 
         
            _context.Reservations.Add(reservation);
            _context.SaveChanges();

            return RedirectToPage("Hotel");
        }
    }
}
