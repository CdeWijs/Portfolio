using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyController : MonoBehaviour
{
    public enum State
    {
        IDLE,
        MOVE,
        SLEEP,
    }
    
    public State currentState;

    public LayerMask detectionLayer;

    private AutoIntensity autoIntensity;
    private Animator animator;
    private NavMeshAgent agent;
    private Collider[] moveCollider;
    private float moveRadius = 5;

    private void Start()
    {
        currentState = State.SLEEP;
        autoIntensity = FindObjectOfType<AutoIntensity>();
        animator = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
    }

    void Update()
    {
        switch (currentState)
        {
            case State.IDLE:
                IdleState();
                break;

            case State.MOVE:
                MoveState();
                break;

            case State.SLEEP:
                SleepState();
                break;
        }
    }

    private void IdleState()
    {
        animator.SetBool("isIdle", true);
        animator.SetBool("isMoving", false);
        animator.SetBool("isSleeping", false);
        agent.enabled = true;

        if (agent.enabled == true)
        {
            moveCollider = Physics.OverlapSphere(transform.position, moveRadius, detectionLayer);

            if (moveCollider.Length > 0)
            {
               currentState = State.MOVE;
            }
        }

        if (autoIntensity.dot > 0)
        {
            currentState = State.SLEEP;
        }
    }

    private void MoveState()
    {
        agent.SetDestination(moveCollider[0].transform.position);
        animator.SetBool("isIdle", false);
        animator.SetBool("isMoving", true);
        animator.SetBool("isSleeping", false);

        if (moveCollider.Length > 10) // doesn't work yet
        {
            currentState = State.IDLE;
        }

        if (autoIntensity.dot > 0)
        {
            currentState = State.SLEEP;
        }
    }

    private void SleepState()
    {
        animator.SetBool("isSleeping", true);
        animator.SetBool("isMoving", false);
        animator.SetBool("isIdle", false);
        agent.enabled = false;

        if (autoIntensity.dot <= 0)
        {
            currentState = State.IDLE;
        }
    }
}
