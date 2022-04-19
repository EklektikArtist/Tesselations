#pragma once
/*--------------------------------------------------------------------------------

    Name:
        cls_sector.h

    Description:
        Header for sector class

--------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------

    Name:
        Sector

    Description:
        Storage for sector data

--------------------------------------------------------------------------------*/


class Sector
    {
    /*------------------------------------------------
    Class Variables
    ------------------------------------------------*/
    Uint8               c_world_sector_cnt;
    int                 c_total_width;    /* red                               */
    int                 c_total_height;    /* red                               */
    int                 c_border_width;

    Uint8               c_loc_id;
    std::vector<Hub>    c_loc_hubs;               /* vector of hubs for sim            */
    std::vector<Item>   c_loc_items;              /* vector of items for sim           */
    
    std::vector<Hub>    c_lfrn_hubs;               /* vector of hubs for sim            */
    std::vector<Item>   c_lfrn_items;              /* vector of items for sim           */

    
    public: Sector 
    (
        void
    )
        {
        c_total_width = 500;
        c_total_height = 1000;
        c_border_width = 50;
        c_loc_id = 0;
        c_world_sector_cnt = 1;
        }
    
    public: Sector 
    (
    Uint8               i_world_sector_cnt,
    int                 i_total_width,
    int                 i_total_height,
    int                 i_border_width,
    Uint8               i_loc_id
    )
        {
        i_world_sector_cnt = i_world_sector_cnt;
        i_total_width = i_total_width;
        i_total_height = i_total_height;
        c_border_width = i_border_width;
        c_loc_id = i_loc_id;
        }

    

    /*----------------------------------------------------------------------------

    Name:
        get_alpha

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_lsector_id
    (
    void
    )
        {
        if( c_world_sector_cnt == 1 )
            {
            return( c_loc_id );
            }
        else
            {
            if ( c_loc_id == 0 )
                { 
                return( c_world_sector_cnt - 1 );
                }
            else
                {
                return( c_loc_id - 1 );
                }
            }
        }
          

    /*----------------------------------------------------------------------------

    Name:
        get_alpha

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: Uint8 get_usector_id
    (
    void
    )
        {
        if( c_world_sector_cnt == 1 )
            {
            return( c_loc_id );
            }
        else
            {
            if ( c_loc_id == c_world_sector_cnt - 1 )
                {
                return( 0 );
                }
            else
                {
                return( c_loc_id + 1 );
                }
            }
        }
          

    /*----------------------------------------------------------------------------

    Name:
        set_world_sector_cnt

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: void set_world_sector_cnt
    (
    Uint8               i_world_sector_cnt
    )
        {
        c_world_sector_cnt = i_world_sector_cnt;
        }
          
          

    /*----------------------------------------------------------------------------

    Name:
        set_world_sector_cnt

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: void set_id
    (
    Uint8               i_id
    )
        {
        c_loc_id = i_id;
        }


    /*----------------------------------------------------------------------------

    Name:
        get_items

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: std::vector<Item>* get_items
    (
    void
    )
        {
        return( &c_loc_items );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        get_items

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: std::vector<Hub>* get_hubs
    (
    void
    )
        {
        return( &c_loc_hubs );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        get_items

    Description:
        Return the color's alpha hue

    ----------------------------------------------------------------------------*/

    public: std::vector<Hub>* get_lfrn_hubs
    (
    void
    )
        {
        return( &c_lfrn_hubs );
        }
          

    /*----------------------------------------------------------------------------

    Name:
        get_items

    Description:

    ----------------------------------------------------------------------------*/

    public: void send_hub
    (
    Hub * i_hub,
    sector_state dir
    )
        {
    int errclass,resultlen;
    std::vector<Uint8>hub_data;
    i_hub->to_array( hub_data );

    uint8_t trg_sec = dir == OUT_OF_SECTOR_POS ? get_usector_id() : dir == OUT_OF_SECTOR_NEG ? get_lsector_id() : c_loc_id;
    int ierr= MPI_Send( hub_data.data(), hub_data.size(), MPI_CHAR, trg_sec, 0, MPI_COMM_WORLD);
      char err_buffer[MPI_MAX_ERROR_STRING];
    if( ierr != MPI_SUCCESS) 
        {
        MPI_Error_class(ierr,&errclass);
        if(errclass== MPI_ERR_RANK) 
            {
            fprintf(stderr,"Invalid rank used in MPI send call\n");
            MPI_Error_string(ierr,err_buffer,&resultlen);
            fprintf(stderr,err_buffer);
            }
        }
        
        }


/*--------------------------------------------------------------------------------

    Name:
        send_collision_msg

    Description:
        Initialize brains

--------------------------------------------------------------------------------*/

void send_collision_msg
(
    int     type,
    int     hub_id,
    coll_msg coll
)
    {    
    }
    };
