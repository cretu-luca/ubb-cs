using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace MyApp.Namespace
{
    public class LoginModel : PageModel
    {
        public void OnGet()
        {
            
        }

        public IActionResult OnPost()
        {
            String username = Request.Form["username"];
            HttpContext.Session.SetString("username", username);

            return RedirectToPage("/Index");
        }
    }
}
