//

#include <stdint.h>

#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)
#define VIRTIO_GPU_FLAG_FENCE (1 << 0) 
 
enum virtio_gpu_ctrl_type { 
 
        /* 2d commands */ 
        VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100, 
        VIRTIO_GPU_CMD_RESOURCE_CREATE_2D, 
        VIRTIO_GPU_CMD_RESOURCE_UNREF, 
        VIRTIO_GPU_CMD_SET_SCANOUT, 
        VIRTIO_GPU_CMD_RESOURCE_FLUSH, 
        VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D, 
        VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING, 
        VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING, 
        VIRTIO_GPU_CMD_GET_CAPSET_INFO, 
        VIRTIO_GPU_CMD_GET_CAPSET, 
        VIRTIO_GPU_CMD_GET_EDID, 
 
        /* cursor commands */ 
        VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300, 
        VIRTIO_GPU_CMD_MOVE_CURSOR, 
 
        /* success responses */ 
        VIRTIO_GPU_RESP_OK_NODATA = 0x1100, 
        VIRTIO_GPU_RESP_OK_DISPLAY_INFO, 
        VIRTIO_GPU_RESP_OK_CAPSET_INFO, 
        VIRTIO_GPU_RESP_OK_CAPSET, 
        VIRTIO_GPU_RESP_OK_EDID, 
 
        /* error responses */ 
        VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200, 
        VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY, 
        VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID, 
        VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID, 
        VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID, 
        VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER, 
}; 

enum virtio_gpu_formats { 
        VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1, 
        VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2, 
        VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3, 
        VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4, 
 
        VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67, 
        VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68, 
 
        VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121, 
        VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134, 
}; 
 
typedef uint32_t le32;
typedef uint64_t le64;

struct virtio_gpu_ctrl_hdr { 
        le32 type; 
        le32 flags; 
        le64 fence_id; 
        le32 ctx_id; 
        le32 padding; 
};


struct virtio_gpu_resource_create_2d { 
        struct virtio_gpu_ctrl_hdr hdr; 
        le32 resource_id; 
        le32 format; 
        le32 width; 
        le32 height; 
}; 

struct virtio_gpu_config {
        le32 events_read;
        le32 events_clear;
        le32 num_scanouts;
        le32 reserved;
};
 

