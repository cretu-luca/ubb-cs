using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication4;

namespace MyApp.Namespace
{
    public class LoginModel : PageModel
    {
        private readonly AppDbContext _context;

        public LoginModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
        }

        public IActionResult OnPost()
        {
            String name = Request.Form["name"];
            String date = Request.Form["date"];
            String destination = Request.Form["destination"];
            
            HttpContext.Session.SetString("name", name);
            HttpContext.Session.SetString("date", date);
            HttpContext.Session.SetString("destination", destination);
            
            return RedirectToPage("/Menu");
        }
    }
}
