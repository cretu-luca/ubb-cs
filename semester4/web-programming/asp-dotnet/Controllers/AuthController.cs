// Controllers/AccountController.cs
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using asp_dotnet.Models;

namespace asp_dotnet.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class AuthController : ControllerBase
    {
        private readonly ApplicationDatabaseContext context;

        public AuthController(ApplicationDatabaseContext context)
        {
            this.context = context;
        }

        public class LoginModel
        {
            public string Username { get; set; }
            public string Password { get; set; }
        }

        [HttpPost("Login")]
        public async Task<IActionResult> Login([FromBody] LoginModel model)
        {
            var user = context.Users.FirstOrDefault(u => 
                u.Username == model.Username && u.Password == model.Password);

            if (user == null)
            {
                return Unauthorized(new { message = "Invalid credentials" });
            }

            var claims = new List<Claim>
            {
                new Claim(ClaimTypes.Name, user.Username)
            };

            var identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
            var principal = new ClaimsPrincipal(identity);
            
            var cookieOptions = new CookieOptions
            {
                HttpOnly = true,
                Expires = DateTime.UtcNow.AddDays(7),
                SameSite = SameSiteMode.None,
                Secure = false
            };

            await HttpContext.SignInAsync(
                CookieAuthenticationDefaults.AuthenticationScheme, 
                principal,
                new AuthenticationProperties
                {
                    IsPersistent = true,
                    ExpiresUtc = DateTimeOffset.UtcNow.AddDays(7),
                    IssuedUtc = DateTimeOffset.UtcNow
                });

            return Ok(new { message = "Login successful" });
        }

        [HttpGet("Logout")]
        public async Task<IActionResult> Logout()
        {
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
            return Ok(new { message = "Logout successful" });
        }

        [HttpGet("CheckAuth")]
        public IActionResult CheckAuth()
        {
            if (HttpContext.User.Identity.IsAuthenticated)
            {
                var username = HttpContext.User.Identity.Name;
                return Ok(new { 
                    isAuthenticated = true, 
                    username = username 
                });
            }
            
            return Unauthorized(new { 
                isAuthenticated = false, 
                message = "User is not authenticated" 
            });
        }
    }
}