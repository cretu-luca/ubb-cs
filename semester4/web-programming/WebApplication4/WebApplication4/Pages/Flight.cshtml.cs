using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication4;
using WebApplication4.Models;

namespace MyApp.Namespace
{
    public class FlightModel : PageModel
    {
        private readonly AppDbContext _context;
        public ICollection<Flight> Flights { get; set; } = new List<Flight>();

        public FlightModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            List<Flight> flights = _context.Flights.ToList();
            List<Flight> flightsWithAvailableSeats = new List<Flight>();
            
            String destination = HttpContext.Session.GetString("destination");
            String date = HttpContext.Session.GetString("date");
            

            foreach (var flight in flights)
            {
                if (flight.AvailableSeats > 0 && flight.Destination == destination && flight.Date == date)
                {
                    flightsWithAvailableSeats.Add(flight);
                }
            }
            
            Flights = flightsWithAvailableSeats;
        }

        public IActionResult OnPost()
        {
            String id = Request.Form["id"];

            Flight flight = _context.Flights.Find(Int32.Parse(id));
            flight.AvailableSeats -= 1;
            
            _context.Flights.Update(flight);
            
            Reservation reservation = new Reservation();
            reservation.Person = HttpContext.Session.GetString("name");
            reservation.Type = "Flight";
            reservation.ReservedResourceId = int.Parse(id); 
         
            _context.Reservations.Add(reservation);
            _context.SaveChanges();

            return RedirectToPage("Flight");
        }
    }
}
