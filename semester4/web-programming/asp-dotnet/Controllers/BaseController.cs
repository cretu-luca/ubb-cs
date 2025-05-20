using Microsoft.AspNetCore.Mvc;
using asp_dotnet.Repository;
using Microsoft.AspNetCore.Authorization;

namespace asp_dotnet.Controllers
{
    // [Authorize]
    [Route("[controller]")]
    [ApiController]
    public class BaseController<T> : ControllerBase where T : class
    {
        private IBaseRepository<T> repository;

        public BaseController(IBaseRepository<T> repository)
        {
            this.repository = repository;
        }

        [HttpGet("GetAll")]
        public async Task<ActionResult<IEnumerable<T>>> GetAll()
        {
            var entities = await this.repository.GetAllAsync();
            return Ok(entities);
        }

        [HttpGet("GetById/{id}")]
        public async Task<ActionResult<T>> GetById(int id)
        {
            var entity = await repository.GetByIdAsync(id);
            if (entity == null)
            {
                return NotFound();
            }
            return Ok(entity);
        }

        [HttpPost("Create")]
        public async Task<ActionResult<T>> Create([FromBody] T entity)
        {
            var created = await repository.AddAsync(entity);
            return Ok(created);
        }

        [HttpPut("Update")]
        public async Task<ActionResult<T>> Update([FromBody] T entity)
        {
            await repository.UpdateAsync(entity);
            return Ok(entity);
        }

        [HttpDelete("Delete/{id}")]
        public async Task<ActionResult> Delete(int id)
        {
            await repository.DeleteAsync(id);
            return Ok(id);
        }
    }
}