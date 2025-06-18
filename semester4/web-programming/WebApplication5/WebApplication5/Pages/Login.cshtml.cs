using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.VisualBasic.CompilerServices;
using WebApplication5;
using WebApplication5.Model;

namespace MyApp.Namespace
{
    public class LoginModel : PageModel
    {
        private readonly AppDbContext _context;
        public String message { get; set; }

        public LoginModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            
        }

        public IActionResult OnPost()
        {
            String username =  Request.Form["username"];
            int password = Int32.Parse(Request.Form["password"]);
            
            User user = _context.Users.SingleOrDefault(u => u.Username == username);
            if (user == null)
            {
                message = "no user with this username";
                return Page();
            }
            
            if (user.Password != password)
            {
                message = "passwords do not match";
                return Page();
            }
            
            message = "logged in";
            
            HttpContext.Session.SetInt32("id", user.Id);
            HttpContext.Session.SetString("username", user.Username);
            HttpContext.Session.SetInt32("password", user.Password);
            
            return RedirectToPage("/Home");
        }
    }
}
