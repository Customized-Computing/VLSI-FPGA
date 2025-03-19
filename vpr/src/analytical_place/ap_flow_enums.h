/**
 * @file
 * @author  Alex Singer
 * @date    February 2025
 * @brief   Enumerations used by the Analytical Placement Flow.
 */

#pragma once

/**
 * @brief The type of a Global Placer.
 *
 * The Analytical Placement flow may implement different Global Placers. This
 * enum can select between these different Global Placers.
 */
enum class e_ap_global_placer {
    // Global placers based on the the SimPL paper.
    SimPL_BiParitioning, ///< Global Placer based on the SimPL technique to Global Placement. Uses a quadratic solver and a bi-partitioning Partial Legalizer.
    SimPL_FlowBased      ///< Global Placer based on the SimPL technique to Global Placement. Uses a quadratic solver and a multi-commodity-flow-baed Partial Legalizer.
};

/**
 * @brief The type of a Full Legalizer.
 *
 * The Analytical Placement flow may implement different Full Legalizers. This
 * enum can select between these different Full Legalizers.
 */
enum class e_ap_full_legalizer {
    Naive,  ///< The Naive Full Legalizer, which clusters atoms placed in the same tile and tries to place them in that tile according to the flat placement.
    APPack,  ///< The APPack Full Legalizer, which uses the flat placement to improve the Packer and Placer.
    Basic_Min_Disturbance ///< The Basic Min. Disturbance Full Legalizer, which tries to reconstruct a clustered placement that is as close to the incoming flat placement as it can.
};

/**
 * @brief The type of a Detailed Placer.
 *
 * The Analytical Placement flow may implement different Detailed Placers. This
 * enum can select between these different Detailed Placers.
 */
enum class e_ap_detailed_placer {
    Identity,           ///< The Identity Detailed Placer, which does not perform any optimizations on the legalized placement. Needed as a placeholder.
    Annealer            ///< The Annealer Detailed Placer, which runs the annealer found in the Place part of the VPR flow (using the same options as the Placement stage).
};

