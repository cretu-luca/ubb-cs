using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using asp_dotnet.Model;
using asp_dotnet.Repository;

namespace asp_dotnet.Controller
{
    [Route("[controller]")]
    [ApiController]
    public class AuthController : ControllerBase
    {
        private readonly ISoftwareDeveloperRepository softwareDeveloperRepository;

        public AuthController(ISoftwareDeveloperRepository userRepository)
        {
            this.softwareDeveloperRepository = userRepository;
        }
        
        public record LoginRequest(string Username);

        [HttpPost("Login")]
        public async Task<IActionResult> Login([FromBody] LoginRequest request)
        {
            var user = await softwareDeveloperRepository.GetSoftwareDeveloperByUsername(request.Username);

            if (user == null)
            {
                return Unauthorized(new { message = "User not found" });
            }

            var claims = new List<Claim>
            {
                new Claim(ClaimTypes.NameIdentifier, user.Id.ToString()),
                new Claim(ClaimTypes.Name, user.Name)
            };

            var identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
            var principal = new ClaimsPrincipal(identity);

            await HttpContext.SignInAsync(
                CookieAuthenticationDefaults.AuthenticationScheme, 
                principal,
                new AuthenticationProperties
                {
                    IsPersistent = true,
                    ExpiresUtc = DateTimeOffset.UtcNow.AddDays(7)
                });

            return Ok(new { message = "Login successful", userId = user.Id, username = user.Name });
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
                var userId = HttpContext.User.FindFirstValue(ClaimTypes.NameIdentifier);
                return Ok(new { 
                    isAuthenticated = true, 
                    username = username,
                    userId = userId
                });
            }
            
            return Unauthorized(new { 
                isAuthenticated = false, 
                message = "User is not authenticated" 
            });
        }
    }
}