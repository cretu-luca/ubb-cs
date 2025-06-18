using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication5;
using WebApplication5.Model;

namespace MyApp.Namespace
{
    public class AllModel : PageModel
    {
        private readonly AppDbContext _context;
        public List<Reservation> Reservations { get; set; }

        public AllModel(AppDbContext context)
        {
            _context = context;
            Reservations = new List<Reservation>();
        }
        
        public void OnGet()
        {
            Reservations = _context.Reservations.Where(r => r.UserId == HttpContext.Session.GetInt32("id")).ToList();
        }
    }
}
