using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication3;
using WebApplication3.Models;

namespace MyApp.Namespace
{
    public class LoginModel : PageModel
    {
        private readonly AppDbContext _context;
        public String message { get; set; }

        public LoginModel(AppDbContext context)
        {
            _context = context;
            message = "";
        }
        
        public void OnGet()
        {
            
        }

        public IActionResult OnPost()
        {
            String username = Request.Form["username"];
            SoftwareDeveloper user = _context.Developers.Where(d => d.Name == username).SingleOrDefault();

            if (user != null)
            {
                HttpContext.Session.SetString("username", user.Name);
            }
            else
            {
                message = "Username not found";
            }
            
            return RedirectToPage("/Home");
        }
    }
}
