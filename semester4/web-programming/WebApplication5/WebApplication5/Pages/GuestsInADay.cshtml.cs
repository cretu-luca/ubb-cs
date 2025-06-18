using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication5;
using WebApplication5.Model;

namespace MyApp.Namespace
{
    public class GuestsInADayModel : PageModel
    {
        private readonly AppDbContext _context;
        public int NumberOfGuests { get; set; }

        public GuestsInADayModel(AppDbContext context)
        {
            _context = context;
            NumberOfGuests = 0;
        }
        
        public void OnGet()
        {
            
        }

        public void OnPost()
        {
            DateTime date = DateTime.Parse(Request.Form["date"]);

            int currnetNumberOfGuests = 0;
            
            List<Reservation> reservations = new List<Reservation>();
            foreach (Reservation reservation in _context.Reservations)
            {
                if (date > reservation.CheckInDate && date < reservation.CheckOutDate)
                {
                    currnetNumberOfGuests += reservation.NumberOfGuests;
                }
            }
            
            NumberOfGuests = currnetNumberOfGuests;
        }
    }
}
